// include/dorm_energy/infrastructure/simulation/synthetic_data_generator.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/domain/simulation/idata_generator.hpp"

#include <random>
#include <chrono>

namespace dorm_energy::simulation
{
    class SyntheticDataGenerator : public IDataGenerator
    {
    public:
        explicit SyntheticDataGenerator(
            unsigned seed = 42,
            bool inject_anomalies = false,
            double anomaly_rate = 0.03);

        void setSeed(unsigned seed) override;

        core::ReadingsBatch generate() const override;
        core::ReadingsBatch generate_for_days(int days) const override;

    private:
        mutable std::mt19937 rng_;
        bool inject_anomalies_;
        double anomaly_rate_;

        core::SensorReading generate_one_reading(
            std::chrono::system_clock::time_point base_time,
            int reading_index) const;
    };

} // namespace dorm_energy::simulation