// include/dorm_energy/core/measurement.hpp
#pragma once

#include <chrono>
#include <vector>
#include <string>

namespace dorm_energy::core {

/**
 * @brief Измерение потребляемой мощности
 */

using Clock = std::chrono::system_clock;
using TimePoint = Clock::time_point;

struct PowerMeasurement {
    TimePoint timestamp{};
    double power_kw{0.0};
    bool is_anomaly{false};

    PowerMeasurement() = default;

    PowerMeasurement(TimePoint ts, double power, bool anomaly = false)
        : timestamp{ts}, power_kw{power}, is_anomaly{anomaly} {}
};

/**
 * @brief Тип для хранения последовательности измерений мощности 
 */
using SimulationData = std::vector<PowerMeasurement>;

/**
 * @brief Преобразует PowerMeasurement в удобную строку для вывода
 * @return строка в формате "YYYY-MM-DD HH:MM | X.XX кВт | аномалия: ДА/нет"
 */
std::string to_string(const PowerMeasurement &m);

} // namespace dorm_energy::core