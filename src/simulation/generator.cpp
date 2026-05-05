// src/simulation/generator.cpp
#include "dorm_energy/simulation/generator.hpp"
#include <format>
#include <iostream>
#include <chrono>
#include <random>

namespace dorm_energy::simulation {

SyntheticDataGenerator::SyntheticDataGenerator(GeneratorConfig config)
    : config_{std::move(config)}
{
    if (config_.days < 1 || config_.days > 365) {
        config_.days = 30;
    }
}

core::SimulationData SyntheticDataGenerator::generate() const
{
    return generate_deterministic(
        config_.days,
        config_.seed,
        config_.inject_anomalies,
        config_.anomaly_rate);
    ;
}

core::SimulationData SyntheticDataGenerator::generate_deterministic(
    int days,
    unsigned seed,
    bool inject_anomalies,
    double anomaly_rate)
{
    core::SimulationData data;
    data.reserve(static_cast<size_t>(days) * 24); // оптимизация памяти

    std::mt19937 gen{seed}; // ← ОДИН генератор на всю симуляцию

    // Фиксированная начальная дата (чтобы при seed=42 всегда были одинаковые данные)
    auto base_time = std::chrono::sys_days{
        std::chrono::year{2025} / std::chrono::January / 1};

    std::chrono::weekday start_dow{base_time};

    for (int d = 0; d < days; ++d)
    {
        int day_of_week = (start_dow + std::chrono::days{d}).c_encoding();

        auto day_start = base_time + std::chrono::days{d};

        // Вызываем статический generate_day и передаём параметры аномалий
        auto day_data = generate_day(
            day_of_week,
            day_start,
            gen,
            inject_anomalies,
            anomaly_rate);

        data.insert(data.end(), day_data.begin(), day_data.end());
    }

    return data;
}

core::SimulationData SyntheticDataGenerator::generate_day(
    int day_of_week,
    core::TimePoint day_start,
    std::mt19937 &gen,
    bool inject_anomalies,
    double anomaly_rate)
{
    core::SimulationData day_data;
    day_data.reserve(24);

    // Базовые уровни потребления
    double night_base   = 5.0;
    double morning_peak = 25.0;
    double day_base     = 12.0;
    double evening_peak = 35.0;

    if (day_of_week >= 5)
    { // 5 и 6 — выходные
        morning_peak *= 0.6;
        evening_peak *= 0.7;
    }

    std::normal_distribution<double> noise(0.0, 2.5);
    std::uniform_int_distribution<int> anomaly_dist(0, 999);

    for (int hour = 0; hour < 24; ++hour)
    {
        double base = night_base;
        if (hour >= 7 && hour < 10)
            base = morning_peak;
        else if (hour >= 10 && hour < 17) base = day_base;
        else if (hour >= 17 && hour < 23) base = evening_peak;

        double power = base + noise(gen);
        if (power < 0.0) power = 0.0;

        bool is_anomaly = false;
        if (inject_anomalies &&
            (static_cast<double>(anomaly_dist(gen)) / 1000.0 < anomaly_rate))
        {
            power *= 2.8;
            is_anomaly = true;
        }

        auto current_time = day_start + std::chrono::hours(hour);

        day_data.emplace_back(current_time, power, is_anomaly);
    }

    return day_data;
}

} // namespace dorm_energy::simulation

// как лучше оформлять код