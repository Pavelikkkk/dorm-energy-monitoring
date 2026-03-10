// Tests

#include "../include/measurement.hpp"
#include "../include/simulator.hpp"
#include "../include/anomaly_detector.hpp"
#include <iostream>

int main() {  
    std::cout << "Running tests...\n";
    
    auto data = generate_simulation(7);  
    detect_anomalies(data);
    
    std::cout << "Tests completed.\n";
    return 0;
}