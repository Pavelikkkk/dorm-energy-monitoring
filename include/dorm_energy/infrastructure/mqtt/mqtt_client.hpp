// include/dorm_energy/infrastructure/mqtt/mqtt_client.hpp
#pragma once

#include "dorm_energy/domain/mqtt/imqtt_connection.hpp"
#include "dorm_energy/domain/mqtt/imqtt_subscription.hpp"
#include "dorm_energy/domain/mqtt/imqtt_message_dispatcher.hpp"
#include "dorm_energy/application/imessage_handler.hpp"

namespace dorm_energy::mqtt
{

    class MqttClient
        : public dorm_energy::mqtt::IMqttConnection,
          public dorm_energy::mqtt::IMqttSubscription,
          public dorm_energy::mqtt::IMqttMessageDispatcher
    {
    public:
        MqttClient();
        ~MqttClient() override;

        bool connect(const std::string &broker = "tcp://127.0.0.1:1883",
                     const std::string &clientId = "dorm-energy") override;

        bool isConnected() const override;

        bool start() override;
        void stop() override;
        void setMode(dorm_energy::mqtt::MqttMode mode) override;

        void subscribe(const std::string &topic) override;
        void subscribe(const std::vector<std::string> &topics) override;

        void unsubscribe(const std::string &topic) override;

        void setHandler(std::unique_ptr<application::IMessageHandler> handler) override;

        using MessageCallback = dorm_energy::mqtt::IMqttMessageDispatcher::MessageCallback;
        void setMessageCallback(MessageCallback callback) override;

    private:
        dorm_energy::mqtt::MqttMode currentMode_ = dorm_energy::mqtt::MqttMode::Simulation;

        std::unique_ptr<application::IMessageHandler> handler_;
        MessageCallback messageCallback_ = nullptr;

        bool isConnected_ = false;
        // std::unique_ptr<paho::mqtt::async_client> mqttClient_ = nullptr;
    };

} // namespace dorm_energy::mqtt