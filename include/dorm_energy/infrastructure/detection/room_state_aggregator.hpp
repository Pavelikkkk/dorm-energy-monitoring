#pragma once

#include "dorm_energy/core/room_state.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <optional>
#include <unordered_map>

namespace dorm_energy::detection
{

    class RoomStateAggregator
    {
    public:
        std::optional<core::RoomState> update(
            const core::SensorReading &reading);

    private:
        std::unordered_map<
            std::string,
            core::RoomState>
            states_;
    };

} // namespace dorm_energy::detection