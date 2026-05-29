// include/dorm_energy/domain/storage/imeasurement_repository.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::storage
{
    /**
     * @brief Интерфейс для сохранения показаний датчиков
     */
    class IMeasurementRepository
    {
    public:
        virtual ~IMeasurementRepository() = default;

        virtual bool save(const core::SensorReading &reading) = 0; // TODO: переименовать в saveReading
        virtual std::size_t saveBatch(const core::ReadingsBatch &readings) = 0;

        virtual void flush() = 0;

        virtual bool saveAnomaly(const core::SensorReading &reading,
                                 const std::string &anomalyType,
                                 const std::string &severity,
                                 const std::string &description) = 0;

        // virtual void shutdown() = 0;
    };
} // namespace dorm_energy::storage