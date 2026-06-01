
#pragma once
#include "dorm_energy/core/alert_severity.hpp"

namespace dorm_energy::detection
{
    struct AnomalyInfo 
    {
        bool isAnomaly = false;
        std::string anomalyType;
        core::AlertSeverity severity = core::AlertSeverity::Warning;
        std::string description;
    };
} // namespace dorm_energy::detection