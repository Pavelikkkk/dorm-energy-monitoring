#include "dorm_energy/infrastructure/detection/room_state_aggregator.hpp"

#include <optional>

namespace dorm_energy::detection
{

    std::optional<core::RoomState>
    RoomStateAggregator::update(
        const core::SensorReading &reading)
    {
        auto &state =
            states_[reading.deviceId];

        state.roomId =
            reading.deviceId;

        state.timestamp =
            reading.timestamp;

        if (reading.sensorType == "motion")
        {
            state.motion =
                reading.boolValue.value_or(false);
        }
        else if (reading.sensorType == "power")
        {
            state.power =
                reading.value;
        }
        else if (reading.sensorType == "light")
        {
            state.light =
                reading.value;
        }

        return state;
    }

}