// src/dorm_energy/infrastructure/mqtt/message_parser.cpp
#include "dorm_energy/infrastructure/mqtt/message_parser.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <string>
#include <optional>
#include <sstream>
#include <iostream>

namespace dorm_energy::mqtt
{

    bool MessageParser::canParse(const std::string &payload) const
    {
        if (payload.empty())
        {
            return false;
        }
        // проверить наличие ключей "deviceId", "sensorType" .
        return payload.find('{') != std::string::npos &&
               payload.find('}') != std::string::npos;
    }

    std::optional<core::SensorReading> MessageParser::parse(const std::string &payload) const
    {
        if (!canParse(payload))
        {
            std::cerr << "[MessageParser] Couldn't parse payload: " << payload << std::endl;
            return std::nullopt;
        }

        // здесь будет полноценный JSON-парсер

        core::SensorReading reading;
        reading.timestamp = std::chrono::system_clock::now();
        reading.deviceId = "mqtt-device-01";
        reading.sensorType = "power";
        reading.value = 5.67;
        reading.unit = "kW";

        std::cout << "[MessageParser] Successfully parsed: "
                  << core::toString(reading) << std::endl;

        return reading;
    }

} // namespace dorm_energy::mqtt