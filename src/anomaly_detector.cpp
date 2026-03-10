// Anomaly detection using threshold-based rules

#include "../include/measurement.hpp"
#include <iostream>
#include <format>

void detect_anomalies(SimulationData& data) {
    constexpr double HIGH_POWER = 40.0;
    constexpr double NIGHT_LOW  = 2.0;

    for (auto& m : data) {
        int hour = std::localtime(&m.timestamp)->tm_hour;
        double p = m.power_kw;

        if (p > HIGH_POWER) {
            m.is_anomaly = true;
            std::cout << std::format("HIGH POWER at {:02}:00 — {:.1f} kW\n", hour, p);
        }
        else if (hour < 6 && p < NIGHT_LOW) {
            m.is_anomaly = true;
            std::cout << std::format("LOW POWER (night) at {:02}:00 — {:.1f} kW\n", hour, p);
        }
    }
}