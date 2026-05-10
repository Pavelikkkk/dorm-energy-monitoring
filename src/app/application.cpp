// src/app/application.cpp
#include "dorm_energy/app/application.hpp"

#include <iostream>
#include <format>
#include <clocale>
#include <chrono>
#include <thread>

namespace dorm_energy {

Application::Application(logging::Logger logger, mqtt::MqttClient mqtt_client)
    : logger_(std::move(logger))
    , mqtt_client_(std::move(mqtt_client))
    , generator_()
    , detector_()
{
}

int Application::run(int argc, char* argv[])
{
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    CLI::App app{"Dorm Energy Simulator — Имитация энергопотребления в общежитии"};

    bool version_flag{false};
    app.add_flag("--version, -v", version_flag, "Показать версию программы");

    auto* simulate = app.add_subcommand("simulate", "Запустить симуляцию энергопотребления");
    int days{30};
    simulate->add_option("--days,-d", days, "Количество дней симуляции")
            ->default_val(30)
            ->check(CLI::Range(1, 365, "days"));
    bool verbose{false};
    simulate->add_flag("--verbose,-v", verbose, "Подробный вывод");
    bool inject_anomalies{false};
    simulate->add_flag("--anomalies", inject_anomalies, "Включить искусственные аномалии");

    auto* daemon = app.add_subcommand("daemon", "Запустить в режиме демона");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        return app.exit(e);
    }

    if (version_flag) {
        std::cout << "Dorm Energy Simulator v1.1\nАвтор: Pasha\nДата сборки: " << __DATE__ << "\n";
        return 0;
    }

    if (simulate->parsed()) return handle_simulate(*simulate);
    if (daemon->parsed())   return handle_daemon();

    std::cout << app.help() << "\n";
    return 1;
}

int Application::handle_simulate(const CLI::App& subcommand)
{
    int days              = subcommand.get_option("--days")->as<int>();
    bool verbose          = subcommand.get_option("--verbose")->as<bool>();
    bool inject_anomalies = subcommand.get_option("--anomalies")->as<bool>();

    logger_.info("Запуск симуляции");

    simulation::GeneratorConfig gen_config;
    gen_config.days             = days;
    gen_config.inject_anomalies = inject_anomalies;

    logger_.info(std::format("Дней: {} | Аномалии: {}", days,
                             inject_anomalies ? "включены" : "выключены"));

    generator_ = simulation::SyntheticDataGenerator{gen_config};  // временно
    auto data = generator_.generate();
    int anomaly_count = detector_.detect(data);

    logger_.info(std::format("Симуляция завершена. Измерений: {}, аномалий: {}", data.size(), anomaly_count));

    if (verbose) {
        std::cout << "\nПервые 10 измерений:\n";
        for (size_t i = 0; i < std::min<size_t>(10, data.size()); ++i) {
            std::cout << dorm_energy::core::to_string(data[i]) << "\n";
        }
        std::cout << "\nОбнаруженные аномалии:\n";
        for (const auto& m : data) {
            if (m.is_anomaly) std::cout << dorm_energy::core::to_string(m) << "\n";
        }
    }
    return 0;
}

int Application::handle_daemon()
{
    logger_.info("Dorm Energy Simulator запущен в режиме ДЕМОНА");
    logger_.info("MQTT-клиент инициализируется...");

    mqtt_client_.connect();
    mqtt_client_.subscribe("devices/+/power");

    mqtt_client_.set_message_callback([this](const core::PowerMeasurement& m) {
        core::SimulationData data = {m};           
        int count = detector_.detect(data);
        if (count > 0) {
            logger_.warn(std::format("АНОМАЛИЯ ОБНАРУЖЕНА! {:.2f} кВт в {}:{}", 
                                     m.power_kw, m.hour_of_day, "ч"));
        }
    });

    mqtt_client_.start_simulation_mode(); 

    logger_.info("Нажмите Ctrl+C для остановки");

    std::signal(SIGINT,  [](int){ Application::running_ = false; });
    std::signal(SIGTERM, [](int){ Application::running_ = false; });

    while (Application::running_) {
        logger_.debug("Heartbeat — MQTT демон работает");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    logger_.info("daemon остановлен.");
    return 0;
}

} // namespace dorm_energy
