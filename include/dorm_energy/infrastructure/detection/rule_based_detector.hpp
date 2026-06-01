// include/dorm_energy/infrastructure/detection/rule_based_detector.hpp
#pragma once

#include "dorm_energy/domain/detection/istate_detector.hpp"

namespace dorm_energy::detection
{
    class RuleBasedDetector
        : public IStateDetector
    {
    public:
        explicit RuleBasedDetector(
            double maxPowerKw = 5.0);

        bool isAnomaly(
            const core::RoomState &state) const override;

        AnomalyInfo detect(
            const core::RoomState &state) const override;

    private:
        double maxPowerKw_;
    };

} // namespace dorm_energy::detection