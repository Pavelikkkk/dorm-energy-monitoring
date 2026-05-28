// src/dorm_energy/infrastructure/mqtt/mqtt_client.cpp
#include "dorm_energy/infrastructure/mqtt/mqtt_client.hpp"
#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/infrastructure/mqtt/message_parser.hpp"

#include <iostream>
#include <thread>
#include <chrono>

namespace dorm_energy::mqtt
{

    MqttClient::MqttClient()
    {
        // paho.mqtt будет позже
    }

    MqttClient::~MqttClient()
    {
        stop();
    }

    bool MqttClient::connect(const std::string &broker, const std::string &clientId)
    {
        std::cout << "[MqttClient] Connected to " << broker
                  << " (clientId: " << clientId << ")... [SIMULATION MODE]" << std::endl;

        isConnected_ = true;
        return true;
    }

    bool MqttClient::isConnected() const
    {
        return isConnected_;
    }

    bool MqttClient::start()
    {
        if (!isConnected_)
        {
            return false;
        }
        std::cout << "[MqttClient] MQTT the client is running in the mode "
                  << (currentMode_ == MqttMode::Simulation ? "SIMULATION" : "REAL") << std::endl;
        return true;
    }

    void MqttClient::stop()
    {
        if (isConnected_)
        {
            std::cout << "[MqttClient] Stopping the client's MQTT..." << std::endl;
            isConnected_ = false;
        }
    }

    void MqttClient::setMode(MqttMode mode)
    {
        currentMode_ = mode;
        std::cout << "[MqttClient] The operating mode has been changed to: "
                  << (mode == MqttMode::Simulation ? "SIMULATION" : "REAL") << std::endl;
    }

    void MqttClient::subscribe(const std::string &topic)
    {
        std::cout << "[MqttClient] Subscribe to a topic: " << topic << std::endl;
    }

    void MqttClient::subscribe(const std::vector<std::string> &topics)
    {
        std::cout << "[MqttClient] Subscribe to " << topics.size() << " topics" << std::endl;
        for (const auto &t : topics)
        {
            subscribe(t);
        }
    }

    void MqttClient::unsubscribe(const std::string &topic)
    {
        std::cout << "[MqttClient] Unsubscribe from " << topic << std::endl;
    }

    void MqttClient::setHandler(std::unique_ptr<application::IMessageHandler> handler)
    {
        handler_ = std::move(handler);
        std::cout << "[MqttClient] The message handler is installed" << std::endl;
    }

    void MqttClient::setMessageCallback(MessageCallback callback)
    {
        messageCallback_ = std::move(callback);
    }

} // namespace dorm_energy::mqtt