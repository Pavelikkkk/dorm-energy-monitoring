// include/dorm_energy/application/inotifier.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/core/alert_severity.hpp"
#include <string>
#include <vector>

namespace dorm_energy::application
{
    class INotifier
    {
    public:
        virtual ~INotifier() = default;

        virtual bool sendAlert(const core::SensorReading &reading,
                               core::AlertSeverity severity = core::AlertSeverity::Warning,
                               const std::string &reason = "") = 0;

        virtual std::size_t sendAlerts(const std::vector<core::SensorReading> &readings,
                                       core::AlertSeverity severity = core::AlertSeverity::Warning,
                                       const std::string &reason = "") = 0;
    };
} // namespace dorm_energy::application