// src/dorm_energy/detection/anomaly_detector.cpp
#include "dorm_energy/infrastructure/detection/anomaly_detector.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <vector>
#include <algorithm>

namespace dorm_energy::detection
{

    AnomalyDetector::AnomalyDetector(double maxPowerKw)
        : maxPowerKw_(maxPowerKw)
    {
        if (maxPowerKw_ <= 0.0)
        {
            maxPowerKw_ = 25.0;
        }
    }

    bool AnomalyDetector::isAnomaly(const core::SensorReading &reading) const
    {
        // В будущем более сложная логика (ML)

        if (reading.sensorType == "power" || reading.sensorType == "Power")
        {
            return reading.value > maxPowerKw_;
        }

        return false;
    }

    std::vector<core::SensorReading> AnomalyDetector::getAnomalies(
        const core::ReadingsBatch &data) const
    {
        std::vector<core::SensorReading> anomalies;
        anomalies.reserve(data.size());

        for (const auto &reading : data)
        {
            if (isAnomaly(reading))
            {
                anomalies.push_back(reading);
            }
        }

        return anomalies;
    }

    int AnomalyDetector::countAnomalies(const core::ReadingsBatch &data) const
    {
        int count{0};

        for (const auto &reading : data)
        {
            if (isAnomaly(reading))
            {
                ++count;
            }
        }

        return count;
    }

} // namespace dorm_energy::detection