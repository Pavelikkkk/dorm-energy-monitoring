// Common data structures for simulation and analysis

#pragma once

#include <ctime>    
#include <vector>

struct Measurement {
    std::time_t timestamp;
    double power_kw;
    bool is_anomaly{false};
};

using SimulationData = std::vector<Measurement>;