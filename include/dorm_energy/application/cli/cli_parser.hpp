// include/dorm_energy/application/cli/cli_parser.hpp
#pragma once

#include <memory>
#include <string>
#include <CLI/CLI.hpp>

namespace dorm_energy::application::cli
{

    /**
     * @brief Параметры, которые могут приходить из командной строки
     */
    struct CommandOptions
    {
        // Общие
        bool verbose{false};
        bool help{false};

        // simulate command
        int days{30};
        unsigned seed{42};
        bool inject_anomalies{false};
        double anomaly_rate{0.03};

        // daemon command
        std::string mqttBroker{"tcp://127.0.0.1:1883"};
        std::string mqttClientId{"dorm-energy"};
        std::string mqttTopic{"devices/+/power"};
    };

    /**
     * @brief Отвечает за парсинг командной строки и хранение параметров
     */
    class CliParser
    {
    public:
        CliParser();

        /**
         * @brief Парсит аргументы командной строки
         * @return true, если парсинг успешен и нужно продолжать выполнение
         */
        bool parse(int argc, char **argv);

        /**
         * @brief Возвращает все распарсенные параметры
         */
        const CommandOptions &options() const noexcept { return options_; }

        bool isSimulate() const noexcept;
        bool isDaemon() const noexcept;
        bool isHelp() const noexcept;

    private:
        void setupCommands();

        std::unique_ptr<CLI::App> app_;
        CommandOptions options_;

        // Субкоманды
        CLI::App *simulate_cmd_{nullptr};
        CLI::App *daemon_cmd_{nullptr};
    };

} // namespace dorm_energy::application::cli