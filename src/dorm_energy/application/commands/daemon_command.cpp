// src/dorm_energy/application/commands/daemon_command.cpp
#include "dorm_energy/application/commands/daemon_command.hpp"
#include "dorm_energy/application/runtime.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <iostream>
#include <chrono>
#include <thread>

namespace dorm_energy::application
{

    DaemonCommand::DaemonCommand(
        std::shared_ptr<dorm_energy::logging::ILogger> logger,
        std::shared_ptr<dorm_energy::mqtt::IMqttConnection> mqtt_connection,
        std::shared_ptr<dorm_energy::mqtt::IMqttSubscription> mqtt_subscription,
        std::shared_ptr<dorm_energy::mqtt::IMqttMessageDispatcher> mqtt_dispatcher,
        std::unique_ptr<application::IMessageHandler> message_handler)
        : logger_(std::move(logger))
        , mqtt_connection_(std::move(mqtt_connection))
        , mqtt_subscription_(std::move(mqtt_subscription))
        , mqtt_dispatcher_(std::move(mqtt_dispatcher))
        , message_handler_(std::move(message_handler))
    {
        if (!logger_ || !mqtt_connection_ || !mqtt_subscription_ || 
            !mqtt_dispatcher_ || !message_handler_) {
            throw std::invalid_argument("DaemonCommand: all dependencies must be provided");
        }
    }

    int DaemonCommand::execute(const cli::CommandOptions &options)
    {
        logger_->info("Launching Dorm Energy in daemon mode (MQTT listener)...");

        Runtime::setOnStopCallback([this]() {
            logger_->info("A stop signal has been received. Performing a flush...");
            if (message_handler_) {
                message_handler_->flush();
            }
            logger_->info("The daemon has completed its work.");
        });

        Runtime::init();

        bool connected = mqtt_connection_->connect();
        if (!connected) {
            logger_->error("Couldn't connect to the MQTT broker");
            return 1;
        }

        mqtt_dispatcher_->setHandler(std::move(message_handler_));

        mqtt_subscription_->subscribe(options.mqttTopic.empty() ? "devices/+/power" : options.mqttTopic);

        if (!mqtt_connection_->start()) {
            logger_->error("Failed to launch MQTT client");
            return 1;
        }

        logger_->info("The daemon has been successfully launched. Waiting for messages... (Ctrl+C to stop)");

        while (Runtime::isRunning()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            // добавить периодические задач
        }

        mqtt_connection_->stop();

        return 0;
    }

} // namespace dorm_energy::application