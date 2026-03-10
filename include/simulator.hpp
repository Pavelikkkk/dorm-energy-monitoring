//

#pragma once

#include "measurement.hpp"
#include <random>

SimulationData generate_day(int dayOfWeek, std::mt19937& gen);
SimulationData generate_simulation(int days, unsigned int seed = std::random_device{}());