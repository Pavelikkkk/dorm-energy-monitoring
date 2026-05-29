// src/dorm_energy/detection/anomaly_detector.cpp
#include "dorm_energy/infrastructure/detection/anomaly_detector.hpp"

#include <fmt/format.h>

namespace dorm_energy::detection
{

    AnomalyDetector::AnomalyDetector(double maxPowerKw)
        : maxPowerKw_(maxPowerKw)
    {
        if (maxPowerKw_ <= 0.0)
            maxPowerKw_ = 25.0;
    }

    bool AnomalyDetector::isAnomaly(const core::SensorReading &reading) const
    {
        return detect(reading).isAnomaly;
    }

    AnomalyInfo AnomalyDetector::detect(const core::SensorReading &reading) const
    {
        AnomalyInfo info;

        if (reading.sensorType == "power" || reading.sensorType == "Power")
        {
            if (reading.value > maxPowerKw_)
            {
                info.isAnomaly = true;
                info.anomalyType = "high_power";
                info.severity = (reading.value > maxPowerKw_ * 2.0) ? "high" : "medium";
                info.description = fmt::format("Power consumption {:.2f} kW exceeds threshold {:.2f} kW",
                                               reading.value, maxPowerKw_);
            }
        }
        // другие типы аномалий позже

        return info;
    }

    std::vector<core::SensorReading> AnomalyDetector::getAnomalies(const core::ReadingsBatch &data) const
    {
        std::vector<core::SensorReading> anomalies;
        anomalies.reserve(data.size() / 10);

        for (const auto &reading : data)
        {
            if (isAnomaly(reading))
                anomalies.push_back(reading);
        }
        return anomalies;
    }

    int AnomalyDetector::countAnomalies(const core::ReadingsBatch &data) const
    {
        int count = 0;
        for (const auto &reading : data)
        {
            if (isAnomaly(reading))
                ++count;
        }
        return count;
    }

} // namespace dorm_energy::detection