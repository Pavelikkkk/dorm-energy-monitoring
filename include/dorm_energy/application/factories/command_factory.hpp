#pragma once

#include "dorm_energy/application/config/app_config.hpp"

#include <memory>

namespace dorm_energy::application
{
    class DaemonCommand;
    class IMessageHandler;
    class SimulateCommand;
} 

namespace dorm_energy::detection
{
    class IStateDetector;
}

namespace dorm_energy::logging
{
    class ILogger;
}

namespace dorm_energy::mqtt
{
    class IMqttConnection;
    class IMqttMessageDispatcher;
    class IMqttSubscription;
} 

namespace dorm_energy::simulation
{
    class IDataGenerator;
}

namespace dorm_energy::storage
{
    class IMeasurementRepository;
}

namespace dorm_energy::web
{
    class WebServer;
}

namespace dorm_energy::application::factories
{
    class CommandFactory
    {
    public:
        explicit CommandFactory(const AppConfig &config);

        std::unique_ptr<SimulateCommand>
        createSimulateCommand(std::shared_ptr<logging::ILogger> logger,
                              std::unique_ptr<simulation::IDataGenerator> generator,
                              std::unique_ptr<detection::IStateDetector> detector,
                              std::shared_ptr<storage::IMeasurementRepository> repository) const;

        std::unique_ptr<DaemonCommand>
        createDaemonCommand(std::shared_ptr<logging::ILogger> logger,
                            std::shared_ptr<mqtt::IMqttConnection> mqttConnection,
                            std::shared_ptr<mqtt::IMqttSubscription> mqttSubscription,
                            std::shared_ptr<mqtt::IMqttMessageDispatcher> mqttDispatcher,
                            std::unique_ptr<IMessageHandler> messageHandler,
                            std::shared_ptr<web::WebServer> webServer) const;

    private:
        const AppConfig &config_;
    };
} // namespace dorm_energy::application::factories
