#include "dorm_energy/application/factories/command_factory.hpp"

#include "dorm_energy/application/commands/daemon_command.hpp"
#include "dorm_energy/application/commands/simulate_command.hpp"

#include <memory>
#include <utility>

namespace dorm_energy::application::factories
{
    CommandFactory::CommandFactory(const AppConfig &config) : config_(config) {}

    std::unique_ptr<SimulateCommand> CommandFactory::createSimulateCommand(
        std::shared_ptr<logging::ILogger> logger,
        std::unique_ptr<simulation::IDataGenerator> generator,
        std::unique_ptr<detection::IStateDetector> detector,
        std::shared_ptr<storage::IMeasurementRepository> repository) const
    {
        return std::make_unique<SimulateCommand>(std::move(logger), std::move(generator),
                                                 std::move(detector), std::move(repository));
    }

    std::unique_ptr<DaemonCommand> CommandFactory::createDaemonCommand(
        std::shared_ptr<logging::ILogger> logger,
        std::shared_ptr<mqtt::IMqttConnection> mqttConnection,
        std::shared_ptr<mqtt::IMqttSubscription> mqttSubscription,
        std::shared_ptr<mqtt::IMqttMessageDispatcher> mqttDispatcher,
        std::unique_ptr<IMessageHandler> messageHandler,
        std::shared_ptr<web::WebServer> webServer) const
    {
        return std::make_unique<DaemonCommand>(
            std::move(logger), config_, std::move(mqttConnection), std::move(mqttSubscription),
            std::move(mqttDispatcher), std::move(messageHandler), std::move(webServer));
    }
} // namespace dorm_energy::application::factories
