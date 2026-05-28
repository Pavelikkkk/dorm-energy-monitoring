// src/dorm_energy/infrastructure/storage/postgres_repository.cpp
#include "dorm_energy/infrastructure/storage/postgres_repository.hpp"
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <iostream>
#include <pqxx/params> // современный API libpqxx

namespace dorm_energy::storage
{

    PostgresMeasurementRepository::PostgresMeasurementRepository(
        const std::string &connectionString)
        : connectionString_(connectionString)
    {
        try
        {
            connect();
            std::cout << "[PostgresRepository] Successfully connected to TimescaleDB\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "[PostgresRepository] Connection error: " << e.what() << std::endl;
            throw;
        }
    }

    PostgresMeasurementRepository::~PostgresMeasurementRepository()
    {
        if (connection_ && connection_->is_open())
        {
            std::cout << "[PostgresRepository] Database connection closed\n";
        }
    }

    void PostgresMeasurementRepository::connect()
    {
        connection_ = std::make_unique<pqxx::connection>(connectionString_);
        if (!connection_->is_open())
        {
            throw std::runtime_error("Failed to open connection to PostgreSQL");
        }
    }

    bool PostgresMeasurementRepository::save(const core::SensorReading &reading)
    {
        try
        {
            pqxx::work txn{*connection_};

            std::string recorded_at_str = fmt::format("{:%Y-%m-%d %H:%M:%S}", reading.timestamp);

            if (reading.boolValue.has_value())
            {
                txn.exec(
                    R"(
                    INSERT INTO sensor_readings 
                        (recorded_at, device_id, sensor_type, numeric_value, bool_value, unit)
                    VALUES 
                        ($1::timestamptz, $2, $3, $4, $5, $6)
                )",
                    pqxx::params{
                        recorded_at_str,
                        reading.deviceId,
                        reading.sensorType,
                        reading.value,
                        reading.boolValue.value(),
                        reading.unit});
            }
            else
            {
                txn.exec(
                    R"(
                    INSERT INTO sensor_readings 
                        (recorded_at, device_id, sensor_type, numeric_value, bool_value, unit)
                    VALUES 
                        ($1::timestamptz, $2, $3, $4, $5, $6)
                )",
                    pqxx::params{
                        recorded_at_str,
                        reading.deviceId,
                        reading.sensorType,
                        reading.value,
                        nullptr, 
                        reading.unit});
            }

            txn.commit();
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Postgres] Save error: " << e.what() << std::endl;
            return false;
        }
    }

    std::size_t PostgresMeasurementRepository::saveBatch(const core::ReadingsBatch &readings)
    {
        if (readings.empty())
            return 0;

        try
        {
            pqxx::work txn{*connection_};
            std::size_t saved = 0;

            for (const auto &r : readings)
            {
                if (save(r))
                    ++saved;
            }

            txn.commit();
            std::cout << fmt::format("[Postgres] Saved {} out of {} readings\n", saved, readings.size());
            return saved;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[Postgres] Batch save error: " << e.what() << std::endl;
            return 0;
        }
    }

} // namespace dorm_energy::storage