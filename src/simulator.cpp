// Realistic data generation for power consumption simulation

#include "../include/measurement.hpp"
#include <random>
#include <ctime>

SimulationData generate_day(int dayOfWeek, std::mt19937& gen) {
    SimulationData dayData;
    dayData.reserve(24);

    double nightBase   = 5.0;
    double morningPeak = 25.0;
    double dayBase     = 12.0;
    double eveningPeak = 35.0;

    // Weekend adjustment (Saturday = 5, Sunday = 6)
    if (dayOfWeek >= 5) {
        morningPeak *= 0.6;  
        eveningPeak *= 0.7;   
    }

    std::normal_distribution<double> noise(0.0, 2.5);

    std::time_t now = std::time(nullptr);
    for (int hour = 0; hour < 24; ++hour) {
        // Determine base consumption based on time of day
        double base;
        if (hour < 7) {
            base = nightBase;      // Night time (00:00-06:59)
        } else if (hour < 10) {
            base = morningPeak;    // Morning peak (07:00-09:59)
        } else if (hour < 17) {
            base = dayBase;        // Day time (10:00-16:59)
        } else if (hour < 23) {
            base = eveningPeak;    // Evening peak (17:00-22:59)
        } else {
            base = nightBase;      // Late night (23:00-23:59)
        }

        double power = base + noise(gen);
        if (power < 0.0) {
            power = 0.0;
        }

        // Calculate timestamp: going backwards from now
        std::time_t timestamp = now - (23 - hour) * 3600LL;

        dayData.push_back({timestamp, power, false});
    }

    return dayData;
}

SimulationData generate_simulation(int days, unsigned seed = std::random_device{}()) {
    std::mt19937 gen(seed);
    
    SimulationData allData;
    allData.reserve(static_cast<size_t>(days) * 24);

    for (int day = 0; day < days; ++day) {
        SimulationData dayData = generate_day(day % 7, gen);
        
        for (size_t i = 0; i < dayData.size(); ++i) {
            allData.push_back(dayData[i]);
        }
    }

    return allData;
}