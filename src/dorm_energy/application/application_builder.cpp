// src/dorm_energy/application/application_builder.cpp
#include "dorm_energy/application/application_builder.hpp"
#include "dorm_energy/application/application.hpp"

#include "dorm_energy/infrastructure/logging/spdlog_logger.hpp"
#include "dorm_energy/infrastructure/simulation/synthetic_data_generator.hpp"
#include "dorm_energy/infrastructure/detection/anomaly_detector.hpp"
#include "dorm_energy/infrastructure/storage/postgres_repository.hpp"
#include "dorm_energy/infrastructure/handlers/message_handler.hpp"
#include "dorm_energy/infrastructure/notifier/console_notifier.hpp"
#include "dorm_energy/infrastructure/mqtt/mqtt_client.hpp"
#include "dorm_energy/infrastructure/cli/cli_parser.hpp"

namespace dorm_energy::application
{

    ApplicationBuilder::ApplicationBuilder() = default;

    ApplicationBuilder &ApplicationBuilder::withConfig(AppConfig config)
    {
        config_ = std::move(config);
        return *this;
    }

    std::shared_ptr<logging::ILogger> ApplicationBuilder::createLogger()
    {
        static std::shared_ptr<logging::ILogger> logger;

        if (!logger)
        {
            logger = std::make_shared<logging::SpdlogLogger>(config_);
        }

        return logger;
    }

    std::unique_ptr<simulation::IDataGenerator> ApplicationBuilder::createGenerator()
    {
        return std::make_unique<simulation::SyntheticDataGenerator>(
            config_.randomSeed, config_.injectAnomalies);
    }

    std::unique_ptr<detection::IAnomalyDetector> ApplicationBuilder::createDetector()
    {
        return std::make_unique<detection::AnomalyDetector>(25.0);
    }

    std::shared_ptr<storage::IMeasurementRepository> ApplicationBuilder::createRepository()
    {
        if (repository_)
            return repository_;

        try
        {
            std::string connStr = config_.getDbConnectionString();

            std::cout << "[Builder] Connecting to TimescaleDB: "
                      << config_.dbHost << ":" << config_.dbPort
                      << "/" << config_.dbName << std::endl;

            repository_ = std::make_shared<storage::PostgresMeasurementRepository>(connStr);

            std::cout << "[Builder] PostgresMeasurementRepository created successfully\n";
            return repository_;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Builder] Failed to create repository: " << e.what() << std::endl;
            throw;
        }
    }

    std::unique_ptr<application::INotifier> ApplicationBuilder::createNotifier()
    {
        return std::make_unique<notifier::ConsoleNotifier>();
    }

    std::unique_ptr<application::IMessageHandler> ApplicationBuilder::createMessageHandler()
    {
        return std::make_unique<handlers::MessageHandler>(
            createDetector(),
            createRepository(),
            createNotifier());
    }

    std::shared_ptr<mqtt::MqttClient> ApplicationBuilder::createSharedMqttClient()
    {
        static std::shared_ptr<mqtt::MqttClient> sharedClient;

        if (!sharedClient)
        {
            sharedClient = std::make_shared<mqtt::MqttClient>();
            sharedClient->setMode(mqtt::MqttMode::Simulation);
        }

        return sharedClient;
    }
    std::shared_ptr<mqtt::IMqttConnection> ApplicationBuilder::createMqttConnection()
    {
        return createSharedMqttClient();
    }

    std::shared_ptr<mqtt::IMqttSubscription> ApplicationBuilder::createMqttSubscription()
    {
        return createSharedMqttClient();
    }

    std::shared_ptr<mqtt::IMqttMessageDispatcher> ApplicationBuilder::createMqttDispatcher()
    {
        return createSharedMqttClient();
    }

    std::unique_ptr<cli::CliParser> ApplicationBuilder::createCliParser()
    {
        return std::make_unique<cli::CliParser>();
    }

    std::unique_ptr<SimulateCommand> ApplicationBuilder::createSimulateCommand()
    {
        return std::make_unique<SimulateCommand>(
            createLogger(),
            createGenerator(),
            createDetector(),
            createRepository());
    }

    std::unique_ptr<DaemonCommand> ApplicationBuilder::createDaemonCommand()
    {
        return std::make_unique<DaemonCommand>(
            createLogger(),
            createMqttConnection(),
            createMqttSubscription(),
            createMqttDispatcher(),
            createMessageHandler());
    }

    std::unique_ptr<Application> ApplicationBuilder::build()
    {
        config_ = AppConfig::load(); 

        repository_ = createRepository();

        auto cliParser = createCliParser();
        auto simulateCmd = createSimulateCommand();
        auto daemonCmd = createDaemonCommand();

        return std::make_unique<Application>(
            config_,
            std::move(cliParser),
            std::move(simulateCmd),
            std::move(daemonCmd),
            repository_); 
    }

} // namespace dorm_energy::application