// src/dorm_energy/infrastructure/detection/rule_based_detector.cpp
#include "dorm_energy/infrastructure/detection/rule_based_detector.hpp"

namespace dorm_energy::detection
{

    RuleBasedDetector::RuleBasedDetector(double maxPowerKw)
        : maxPowerKw_(maxPowerKw)
    {
        if (maxPowerKw_ <= 0.0)
            maxPowerKw_ = 25.0;
    }

    bool RuleBasedDetector::isAnomaly(const core::RoomState &state) const
    {
        return detect(state).isAnomaly;
    }

    AnomalyInfo RuleBasedDetector::detect( // вынести значения конфиг и задвать с интерфейса
        const core::RoomState &state) const
    {
        AnomalyInfo info;

        if (state.power > maxPowerKw_)
        {
            info.isAnomaly = true;
            info.anomalyType = "high_power";
            info.description =
                "Power consumption exceeds threshold";

            info.severity =
                core::AlertSeverity::Warning;

            return info;
        }

        if (!state.motion &&
            state.light > 500)
        {
            info.isAnomaly = true;

            info.anomalyType =
                "light_without_motion";

            info.description =
                "Light is on but no motion detected";

            info.severity =
                core::AlertSeverity::Info;

            return info;
        }

        if (!state.motion &&
            state.power > 5.0)
        {
            info.isAnomaly = true;

            info.anomalyType =
                "power_without_motion";

            info.description =
                "Power consumption without motion";

            info.severity =
                core::AlertSeverity::Warning;

            return info;
        }

        return info;
    }

} // namespace dorm_energy::detection