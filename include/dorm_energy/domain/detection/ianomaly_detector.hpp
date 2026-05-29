// include/dorm_energy/domain/detection/ianomaly_detector.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include <string>

namespace dorm_energy::detection
{
    struct AnomalyInfo
    {
        bool isAnomaly = false;
        std::string anomalyType;
        std::string severity;
        std::string description;
    };

    class IAnomalyDetector
    {
    public:
        virtual ~IAnomalyDetector() = default;

        virtual bool isAnomaly(const core::SensorReading &reading) const = 0;
        virtual std::vector<core::SensorReading> getAnomalies(const core::ReadingsBatch &data) const = 0;
        virtual int countAnomalies(const core::ReadingsBatch &data) const = 0;

        virtual AnomalyInfo detect(const core::SensorReading &reading) const = 0;
    };

} // namespace dorm_energy::detection