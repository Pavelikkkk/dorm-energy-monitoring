// src/dorm_energy/infrastructure/notifier/console_notifier.cpp
#include "dorm_energy/infrastructure/notifier/console_notifier.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <iostream>
#include <vector>
#include <string>

namespace dorm_energy::notifier
{

    std::string ConsoleNotifier::formatAlert(const core::SensorReading &reading,
                                             const std::string &reason) const
    {
        std::ostringstream oss;
        oss << " [ANOMALY] ";

        if (!reason.empty())
        {
            oss << reason << " — ";
        }

        oss << core::toString(reading);
        return oss.str();
    }

    bool ConsoleNotifier::sendAlert(const core::SensorReading &reading,
                                    const std::string &reason)
    {
        std::cout << formatAlert(reading, reason) << std::endl;
        return true; 
    }

    std::size_t ConsoleNotifier::sendAlerts(const std::vector<core::SensorReading> &readings,
                                            const std::string &reason)
    {
        if (readings.empty())
        {
            return 0;
        }

        std::size_t sent = 0;
        for (const auto &reading : readings)
        {
            if (sendAlert(reading, reason))
            {
                ++sent;
            }
        }

        std::cout << " Dispatched " << sent << " alerts sent to the console\n"
                  << std::endl;
        return sent;
    }

} // namespace dorm_energy::notifier