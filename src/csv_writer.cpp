// csv_writer.cpp
// Export results to CSV format

#include "../include/measurement.hpp"
#include <fstream>
#include <format>
#include <iostream>

void save_to_csv(const SimulationData& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }

    file << "timestamp,power_kw,is_anomaly\n";
    
    for (const auto& m : data) {
        file << m.timestamp << ","
             << std::format("{:.2f}", m.power_kw) << ","
             << (m.is_anomaly ? "1" : "0") << "\n";
    }

    std::cout << "Data saved to: " << filename << "\n";
}