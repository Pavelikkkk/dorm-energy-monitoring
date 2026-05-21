// include/dorm_energy/infrastructure/mqtt/mqtt_client.hpp
#pragma once

#include "dorm_energy/domain/mqtt/imqtt_connection.hpp"
#include "dorm_energy/domain/mqtt/imqtt_subscription.hpp"
#include "dorm_energy/domain/mqtt/imqtt_message_dispatcher.hpp"
#include "dorm_energy/application/imessage_handler.hpp"

namespace dorm_energy::infrastructure::mqtt
{

    /**
     * @brief Основная реализация MQTT-клиента
     *
     * Композитный класс, который реализует все MQTT-интерфейсы.
     * Это удобно для Application и DaemonCommand.
     */
    class MqttClient
        : public domain::mqtt::IMqttConnection,
          public domain::mqtt::IMqttSubscription,
          public domain::mqtt::IMqttMessageDispatcher
    {
    public:
        MqttClient();
        ~MqttClient() override;

        // ====================== IMqttConnection ======================
        void connect(const std::string &broker = "tcp://127.0.0.1:1883",
                     const std::string &clientId = "dorm-energy") override;

        void start() override;
        void stop() override;
        void setMode(domain::mqtt::MqttMode mode) override;

        // ====================== IMqttSubscription ======================
        void subscribe(const std::string &topic = "devices/+/power") override;

        // ====================== IMqttMessageDispatcher ======================
        void setHandler(std::unique_ptr<application::IMessageHandler> handler) override;

        using MessageCallback = domain::mqtt::IMqttMessageDispatcher::MessageCallback;
        void setMessageCallback(MessageCallback callback) override;

    private:
        domain::mqtt::MqttMode currentMode_ = domain::mqtt::MqttMode::Simulation;

        std::unique_ptr<application::IMessageHandler> handler_;
        MessageCallback messageCallback_ = nullptr;

        bool isConnected_ = false;
        // Здесь будет реальный MQTT-клиент (mosquitto или paho)
    };

} // namespace dorm_energy::infrastructure::mqtt