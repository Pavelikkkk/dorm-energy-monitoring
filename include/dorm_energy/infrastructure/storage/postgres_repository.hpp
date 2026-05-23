// include/dorm_energy/infrastructure/storage/postgres_repository.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include "dorm_energy/domain/storage/imeasurement_repository.hpp"

namespace dorm_energy::storage
{

    class PostgresMeasurementRepository : public dorm_energy::storage::IMeasurementRepository
    {
    public:
        explicit PostgresMeasurementRepository(const std::string &connectionString);

        ~PostgresMeasurementRepository() override;

        bool save(const core::SensorReading &reading) override;

        std::size_t saveBatch(const core::ReadingsBatch &readings) override;

        // Позже:
        // core::ReadingsBatch findByDevice(const std::string& deviceId, std::size_t limit) const;
        // std::size_t count() const;

    private:
        std::string connectionString_;

        // std::unique_ptr<pqxx::connection> connection_;                                                                                   // для начала
        // std::shared_ptr<pqxx::connection_pool> pool_;
    };

} // namespace dorm_energy::storage