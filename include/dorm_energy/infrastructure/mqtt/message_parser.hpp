// include/dorm_energy/infrastructure/mqtt/message_parser.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"

#include <string>

namespace dorm_energy::mqtt
{

    class MessageParser
    {
    public:
        MessageParser() = default;

        std::optional<core::SensorReading> parse(const std::string &payload) const;

        bool canParse(const std::string &payload) const;
    };

} // namespace dorm_energy::mqtt