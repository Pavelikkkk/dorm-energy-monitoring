// include/dorm_energy/infrastructure/simulation/synthetic_data_generator.hpp
#pragma once

#include <random>
#include <chrono>

#include "dorm_energy/domain/simulation/idata_generator.hpp"
#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::infrastructure::simulation
{

    /**
     * @brief Реализация генератора синтетических данных
     *
     * Генерирует правдоподобные данные потребления энергии для общежития.
     */
    class SyntheticDataGenerator : public domain::simulation::IDataGenerator
    {
    public:
        explicit SyntheticDataGenerator(unsigned seed = 42, bool inject_anomalies = false);

        core::ReadingsBatch generate() const override;

        // Можно генерировать за N дней
        core::ReadingsBatch generate_for_days(int days) const;

    private:
        mutable std::mt19937 rng_;
        bool inject_anomalies_{false};
        double anomaly_rate_{0.03};

        core::SensorReading generate_one_reading(std::chrono::system_clock::time_point ts) const;
    };

} // namespace dorm_energy::infrastructure::simulation