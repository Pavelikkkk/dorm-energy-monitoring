// include/dorm_energy/application/application_builder.hpp
#pragma once

#include "dorm_energy/application/application.hpp"

#include <memory>

namespace dorm_energy
{
    namespace domain::logging
    {
        class ILogger;
    }
    namespace domain::simulation
    {
        class IDataGenerator;
    }
    namespace domain::detection
    {
        class IAnomalyDetector;
    }
    namespace domain::storage
    {
        class IMeasurementRepository;
    }
    namespace domain::mqtt
    {
        class IMqttConnection;
        class IMqttSubscription;
        class IMqttMessageDispatcher;
    }
    namespace application
    {
        class IMessageHandler;
        class INotifier;
        class CliParser;
        class SimulateCommand;
        class DaemonCommand;
        class DaemonApplication;
    }
}

namespace dorm_energy::application
{

    /**
     * @brief Отвечает за создание всех зависимостей и сборку Application.
     * Это Composition Root приложения.
     */
    class ApplicationBuilder
    {
    public:
        ApplicationBuilder();
        ~ApplicationBuilder() = default;

        /**
         * @brief Собирает и возвращает готовое приложение
         */
        std::unique_ptr<dorm_energy::application::Application> build();

    private:
        // === Фабричные методы создания зависимостей ===
        std::unique_ptr<domain::logging::ILogger> createLogger();
        std::unique_ptr<domain::simulation::IDataGenerator> createGenerator();
        std::unique_ptr<domain::detection::IAnomalyDetector> createDetector();
        std::unique_ptr<domain::storage::IMeasurementRepository> createRepository();
        std::unique_ptr<application::IMessageHandler> createMessageHandler();
        std::unique_ptr<application::INotifier> createNotifier();

        std::unique_ptr<domain::mqtt::IMqttConnection> createMqttConnection();
        std::unique_ptr<domain::mqtt::IMqttSubscription> createMqttSubscription();
        std::unique_ptr<domain::mqtt::IMqttMessageDispatcher> createMqttDispatcher();

        // === Создание команд ===
        std::unique_ptr<CliParser> createCliParser();
        std::unique_ptr<SimulateCommand> createSimulateCommand();
        std::unique_ptr<DaemonCommand> createDaemonCommand();

        // Вспомогательный метод для создания DaemonApplication
        std::unique_ptr<DaemonApplication> createDaemonApplication();
    };

} // namespace dorm_energy::application