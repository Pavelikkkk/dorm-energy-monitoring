// src/detection/anomaly_detector.cpp
#include "dorm_energy/detection/anomaly_detector.hpp"

#include <format>
#include <iostream>
#include <chrono>

namespace dorm_energy::detection {

AnomalyDetector::AnomalyDetector(AnomalyDetectorConfig config)
    : config_{std::move(config)}
{
}

int AnomalyDetector::detect(core::SimulationData &data) const
{
    int anomaly_count{0};

    const auto *zone = std::chrono::locate_zone(config_.timezone);

    for (auto &m : data)
    {

        auto zoned = std::chrono::zoned_time{zone, m.timestamp}; // еще раз повторить chrono библиотеку
        auto local_tp = zoned.get_local_time();

        auto days_since_epoch = std::chrono::floor<std::chrono::days>(local_tp);
        auto hms = std::chrono::hh_mm_ss{local_tp - days_since_epoch};

        bool is_anomaly{false};

        // Правило 1: Слишком высокое потребление
        if (m.power_kw > config_.high_power_threshold)
        {
            is_anomaly = true;
        }
        // Правило 2: Слишком низкое потребление ночью
        else if (m.power_kw < AnomalyDetectorConfig::night_low_threshold &&
                 hms.to_duration() >= AnomalyDetectorConfig::night_start.to_duration() &&
                 hms.to_duration() <= AnomalyDetectorConfig::night_end.to_duration())
        {
            is_anomaly = true;
        }

        if (is_anomaly)
        {
            m.is_anomaly = true;
            anomaly_count++;
        }
    }

    return anomaly_count;
}

std::vector<core::PowerMeasurement> 
AnomalyDetector::get_anomalies(const core::SimulationData& data) const
{
    std::vector<core::PowerMeasurement> anomalies;
    anomalies.reserve(data.size() / 10); // оптимизировать под данные и что за число 10

    for (const auto& m : data) {
        if (m.is_anomaly) {
            anomalies.push_back(m);
        }
    }

    return anomalies;
}

} // namespace dorm_energy::detection