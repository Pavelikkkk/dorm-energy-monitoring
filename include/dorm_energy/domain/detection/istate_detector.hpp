#pragma once

#include "dorm_energy/core/room_state.hpp"
#include "dorm_energy/domain/detection/anomaly_info.hpp" // 

namespace dorm_energy::detection
{

    class IStateDetector
    {
    public:
        virtual ~IStateDetector() = default;

        virtual bool isAnomaly(
            const core::RoomState &state) const = 0;

        virtual AnomalyInfo detect(
            const core::RoomState &state) const = 0;
    };

}