// include/dorm_energy/infrastructure/storage/postgres_repository.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/domain/storage/imeasurement_repository.hpp"

#include <pqxx/pqxx>
#include <memory>
#include <string>

namespace dorm_energy::storage
{

    class PostgresMeasurementRepository : public IMeasurementRepository
    {
    public:
        explicit PostgresMeasurementRepository(const std::string &connectionString);

        ~PostgresMeasurementRepository() override;

        bool save(const core::SensorReading &reading) override;
        std::size_t saveBatch(const core::ReadingsBatch &readings) override;

    private:
        std::string connectionString_;
        std::unique_ptr<pqxx::connection> connection_;

        void connect();
    };

} // namespace dorm_energy::storage