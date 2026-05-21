// include/dorm_energy/infrastructure/detection/anomaly_detector.hpp
#pragma once

#include "dorm_energy/domain/detection/ianomaly_detector.hpp"
#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::infrastructure::detection
{

    /**
     * @brief Простая реализация детектора аномалий на основе пороговых правил
     */
    class AnomalyDetector : public domain::detection::IAnomalyDetector
    {
    public:
        explicit AnomalyDetector(double maxPowerKw = 25.0);

        bool isAnomaly(const core::SensorReading &reading) const override;

        std::vector<core::SensorReading> getAnomalies(const core::ReadingsBatch &data) const override;

        int countAnomalies(const core::ReadingsBatch &data) const override;

    private:
        double maxPowerKw_;
    };

} // namespace dorm_energy::infrastructure::detection