// src/mqtt/mqtt_client.cpp
#include "dorm_energy/mqtt/mqtt_client.hpp"

#include <iostream>
#include <format>
#include <thread>
#include <chrono>

#include "dorm_energy/simulation/generator.hpp"

namespace dorm_energy::mqtt {

struct MqttClient::Impl {
    MessageCallback callback;
    std::thread sim_thread;
};

MqttClient::MqttClient() : impl_(std::make_unique<Impl>()) {}

MqttClient::~MqttClient() {
    if (impl_->sim_thread.joinable()) {
        impl_->sim_thread.join();
    }
}

MqttClient::MqttClient(MqttClient&&) noexcept = default;
MqttClient& MqttClient::operator=(MqttClient&&) noexcept = default;

void MqttClient::connect(const std::string& broker, const std::string& client_id) {
    std::cout << std::format("[MQTT] Подключение к {} как {}\n", broker, client_id);
}

void MqttClient::subscribe(const std::string& topic) {
    std::cout << std::format("[MQTT] Подписка на топик: {}\n", topic);
}

void MqttClient::set_message_callback(MessageCallback callback) {
    impl_->callback = std::move(callback);
}

void MqttClient::start_simulation_mode() {
    if (impl_->sim_thread.joinable()) return;

    impl_->sim_thread = std::thread([this]() {
        simulation::GeneratorConfig cfg;
        cfg.days = 1;
        cfg.inject_anomalies = true;
        simulation::SyntheticDataGenerator gen{cfg};

        while (true) {
            auto day_data = gen.generate();
            for (const auto& m : day_data) {
                if (impl_->callback) {
                    impl_->callback(m);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            }
        }
    });
}

} // namespace dorm_energy::mqtt