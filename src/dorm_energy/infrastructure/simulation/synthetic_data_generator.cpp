// src/dorm_energy/infrastructure/simulation/synthetic_data_generator.cpp
#include "dorm_energy/infrastructure/simulation/synthetic_data_generator.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <chrono>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_set>

namespace dorm_energy::simulation
{

    SyntheticDataGenerator::SyntheticDataGenerator::SyntheticDataGenerator(
        unsigned seed,
        bool inject_anomalies,
        double anomaly_rate)
        : rng_(seed), 
        inject_anomalies_(inject_anomalies), 
        anomaly_rate_(anomaly_rate)
    {
    }

    void SyntheticDataGenerator::setSeed(unsigned seed)
    {
        rng_.seed(seed);
    }

    core::SensorReading SyntheticDataGenerator::generate_one_reading(
        std::chrono::system_clock::time_point base_time,
        int reading_index) const
    {
        static const std::vector<std::string> devices = {
            "kitchen", "bedroom-1", "bedroom-2", "living-room", "bathroom", "corridor"};

        static const std::vector<std::string> sensorTypes = {
            "power", "motion", "temperature", "light"};

        std::uniform_int_distribution<std::size_t> deviceDist(0, devices.size() - 1);
        std::uniform_int_distribution<std::size_t> typeDist(0, sensorTypes.size() - 1);

        std::string deviceId = devices[deviceDist(rng_)];
        std::string sensorType = sensorTypes[typeDist(rng_)];

        auto ms = std::chrono::milliseconds(
            (reading_index * 137) % 900 +
            std::uniform_int_distribution<int>(0, 99)(rng_));

        auto finalTime = base_time + ms;

        core::SensorReading reading;
        reading.timestamp = finalTime;
        reading.deviceId = deviceId;
        reading.sensorType = sensorType;

        if (sensorType == "power")
        {
            std::uniform_real_distribution<double> powerDist(0.2, 8.0);
            reading.value = powerDist(rng_);
            reading.unit = "kW";

            if (inject_anomalies_ &&
                std::uniform_real_distribution<double>(0.0, 1.0)(rng_) < anomaly_rate_)
            {
                reading.value = 25.0 + std::uniform_real_distribution<double>(5.0, 30.0)(rng_);
            }
        }
        else if (sensorType == "motion")
        {
            std::bernoulli_distribution motionDist(0.15);
            reading.boolValue = motionDist(rng_);
            reading.unit = "bool";
        }
        else if (sensorType == "temperature")
        {
            std::normal_distribution<double> tempDist(22.0, 3.0);
            reading.value = tempDist(rng_);
            reading.unit = "°C";
        }
        else if (sensorType == "light")
        {
            std::uniform_real_distribution<double> lightDist(50.0, 800.0);
            reading.value = lightDist(rng_);
            reading.unit = "lux";
        }

        return reading;
    }

    core::ReadingsBatch SyntheticDataGenerator::generate() const
    {
        return generate_for_days(1);
    }

    core::ReadingsBatch SyntheticDataGenerator::generate_for_days(int days) const
    {
        if (days <= 0)
            days = 1;

        core::ReadingsBatch batch;
        batch.reserve(static_cast<std::size_t>(days) * 24 * 12);

        auto now = std::chrono::system_clock::now();
        auto currentTime = now - std::chrono::hours(24 * days);

        std::uniform_int_distribution<int> readingsPerHour(8, 15);

        int globalIndex = 0;

        for (int day = 0; day < days; ++day)
        {
            for (int hour = 0; hour < 24; ++hour)
            {
                int readingsCount = readingsPerHour(rng_);

                for (int i = 0; i < readingsCount; ++i)
                {
                    auto minuteOffset = std::chrono::minutes(
                        std::uniform_int_distribution<int>(0, 59)(rng_));

                    auto baseTs = currentTime + std::chrono::hours(hour) + minuteOffset;

                    batch.push_back(generate_one_reading(baseTs, globalIndex++));
                }
            }
            currentTime += std::chrono::hours(24);
        }

        return batch;
    }

} // namespace dorm_energy::simulation