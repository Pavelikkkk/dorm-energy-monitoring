// include/dorm_energy/domain/storage/imeasurement_repository.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/core/alert_severity.hpp"

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
                                 core::AlertSeverity severity,
                                 const std::string &description,
                                 double score = 0.0) = 0;

        // virtual void shutdown() = 0;
    };
} // namespace dorm_energy::storage