// include/dorm_energy/infrastructure/storage/postgres_repository.hpp
#pragma once

#include "dorm_energy/domain/storage/imeasurement_repository.hpp"
#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::infrastructure::storage
{
    /**
     * @brief Реализация репозитория для PostgreSQL + TimescaleDB
     *
     * Отвечает за сохранение показаний датчиков в базу данных.
     * Использует TimescaleDB (гипертаблицы) для эффективной работы с time-series данными.
     */
    class PostgresMeasurementRepository : public domain::storage::IMeasurementRepository
    {
    public:
        /**
         * @brief Конструктор
         * @param connectionString строка подключения к PostgreSQL
         */
        explicit PostgresMeasurementRepository(const std::string &connectionString);

        ~PostgresMeasurementRepository() override;

        void save(const core::SensorReading &reading) override;

        void saveBatch(const core::ReadingsBatch &readings) override;

        // Можно добавить позже:
        // core::ReadingsBatch findByDevice(const std::string& deviceId, std::size_t limit) const;
        // std::size_t count() const;

    private:
        std::string connectionString_;
        // pqxx::connection* connection_ = nullptr;   // или pqxx::connection_ptr
        // или лучше использовать пул соединений (recommended)
    };

} // namespace dorm_energy::infrastructure::storage