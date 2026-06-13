#pragma once

#include "dorm_energy/application/config/app_config.hpp"
#include "dorm_energy/application/factories/auth_factory.hpp"
#include "dorm_energy/application/factories/cli_factory.hpp"
#include "dorm_energy/application/factories/command_factory.hpp"
#include "dorm_energy/application/factories/detection_factory.hpp"
#include "dorm_energy/application/factories/logger_factory.hpp"
#include "dorm_energy/application/factories/message_handler_factory.hpp"
#include "dorm_energy/application/factories/mqtt_factory.hpp"
#include "dorm_energy/application/factories/notification_factory.hpp"
#include "dorm_energy/application/factories/repository_factory.hpp"
#include "dorm_energy/application/factories/simulation_factory.hpp"
#include "dorm_energy/application/factories/state_factory.hpp"
#include "dorm_energy/application/factories/web_server_factory.hpp"

#include <memory>

namespace dorm_energy::application
{
    class Application;

    class ApplicationBuilder
    {
    public:
        ApplicationBuilder() = default;

        ApplicationBuilder &withConfig(AppConfig config);

        std::unique_ptr<Application> build();

    private:
        AppConfig config_{};

        factories::AuthFactory authFactory_{config_};
        factories::CliFactory cliFactory_{};
        factories::CommandFactory commandFactory_{config_};
        factories::DetectionFactory detectionFactory_{config_};
        factories::LoggerFactory loggerFactory_{config_};
        factories::MessageHandlerFactory messageHandlerFactory_{};
        factories::MqttFactory mqttFactory_{config_};
        factories::NotificationFactory notificationFactory_{config_};
        factories::RepositoryFactory repositoryFactory_{config_};
        factories::SimulationFactory simulationFactory_{config_};
        factories::StateFactory stateFactory_{};
        factories::WebServerFactory webServerFactory_{};
    };

} // namespace dorm_energy::application
