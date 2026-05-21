// include/dorm_energy/application/application.hpp
#pragma once

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
    }
}

namespace dorm_energy::application
{

    /**
     * @brief Главный класс приложения
     */
    class Application
    {
    public:
        Application();
        ~Application() = default;

        int run(int argc, char **argv);

    private:
        void initializeDependencies();


        std::unique_ptr<domain::logging::ILogger> createLogger();
        std::unique_ptr<domain::simulation::IDataGenerator> createGenerator();
        std::unique_ptr<domain::detection::IAnomalyDetector> createDetector();
        std::unique_ptr<domain::storage::IMeasurementRepository> createRepository();
        std::unique_ptr<application::IMessageHandler> createMessageHandler();
        std::unique_ptr<application::INotifier> createNotifier();
        std::unique_ptr<domain::mqtt::IMqttConnection> createMqttConnection();
        std::unique_ptr<domain::mqtt::IMqttSubscription> createMqttSubscription();
        std::unique_ptr<domain::mqtt::IMqttMessageDispatcher> createMqttDispatcher();


        int executeSimulateCommand();
        int executeDaemonCommand();

        std::unique_ptr<domain::logging::ILogger> logger_;
        std::unique_ptr<domain::simulation::IDataGenerator> generator_;
        std::unique_ptr<domain::detection::IAnomalyDetector> detector_;
        std::unique_ptr<domain::storage::IMeasurementRepository> repository_;
        std::unique_ptr<application::IMessageHandler> message_handler_;
        std::unique_ptr<application::INotifier> notifier_;

        std::unique_ptr<domain::mqtt::IMqttConnection> mqtt_connection_;
        std::unique_ptr<domain::mqtt::IMqttSubscription> mqtt_subscription_;
        std::unique_ptr<domain::mqtt::IMqttMessageDispatcher> mqtt_dispatcher_;
    };

} // namespace dorm_energy::application