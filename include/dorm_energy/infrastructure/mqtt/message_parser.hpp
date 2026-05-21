// include/dorm_energy/infrastructure/mqtt/message_parser.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include <string>

namespace dorm_energy::infrastructure::mqtt
{

    /**
     * @brief Парсер MQTT-сообщений (JSON <-> SensorReading)
     */
    class MessageParser
    {
    public:
        MessageParser() = default;

        /**
         * @brief Парсит JSON-сообщение от датчика в SensorReading
         * @param payload JSON-строка из MQTT
         * @param outReading объект, в который будет записан результат
         * @return true, если парсинг успешен
         */
        bool parse(const std::string &payload, core::SensorReading &outReading);

        /**
         * @brief Проверяет, можно ли распарсить сообщение (валидация)
         */
        bool canParse(const std::string &payload) const;
    };

} // namespace dorm_energy::infrastructure::mqtt