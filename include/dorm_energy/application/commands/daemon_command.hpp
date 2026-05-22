// include/dorm_energy/application/commands/daemon_command.hpp
#pragma once

#include "dorm_energy/application/cli/command_options.hpp"

#include "dorm_energy/domain/logging/ilogger.hpp"
#include "dorm_energy/domain/mqtt/imqtt_connection.hpp"
#include "dorm_energy/domain/mqtt/imqtt_subscription.hpp"
#include "dorm_energy/domain/mqtt/imqtt_message_dispatcher.hpp"
#include "dorm_energy/application/imessage_handler.hpp"

#include <memory>

namespace dorm_energy::application
{

    /**
     * @brief Команда запуска демона (долгоживущий процесс)
     */
    class DaemonCommand
    {
    public:
        explicit DaemonCommand(
            std::unique_ptr<domain::logging::ILogger> logger,
            std::unique_ptr<domain::mqtt::IMqttConnection> mqtt_connection,
            std::unique_ptr<domain::mqtt::IMqttSubscription> mqtt_subscription,
            std::unique_ptr<domain::mqtt::IMqttMessageDispatcher> mqtt_dispatcher,
            std::unique_ptr<application::IMessageHandler> message_handler);

        int execute(const cli::CommandOptions &options);

    private:
        std::unique_ptr<domain::logging::ILogger> logger_;
        std::unique_ptr<domain::mqtt::IMqttConnection> mqtt_connection_;
        std::unique_ptr<domain::mqtt::IMqttSubscription> mqtt_subscription_;
        std::unique_ptr<domain::mqtt::IMqttMessageDispatcher> mqtt_dispatcher_;
        std::unique_ptr<application::IMessageHandler> message_handler_;
    };

} // namespace dorm_energy::application