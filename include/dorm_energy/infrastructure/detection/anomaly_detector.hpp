// include/dorm_energy/infrastructure/detection/anomaly_detector.hpp
#pragma once

#include "dorm_energy/domain/detection/ianomaly_detector.hpp"
#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::detection
{

    class AnomalyDetector : public dorm_energy::detection::IAnomalyDetector
    {
    public:
        explicit AnomalyDetector(double maxPowerKw = 25.0);

        bool isAnomaly(const core::SensorReading &reading) const override;

        std::vector<core::SensorReading> getAnomalies(const core::ReadingsBatch &data) const override;

        int countAnomalies(const core::ReadingsBatch &data) const override;

    private:
        double maxPowerKw_;
    };

} // namespace dorm_energy::detection