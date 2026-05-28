// src/dorm_energy/application/commands/simulate_command.cpp
#include "dorm_energy/application/commands/simulate_command.hpp"
#include "dorm_energy/core/measurement.hpp"

#include <iostream>

namespace dorm_energy::application
{

    SimulateCommand::SimulateCommand(
        std::shared_ptr<dorm_energy::logging::ILogger> logger,
        std::unique_ptr<dorm_energy::simulation::IDataGenerator> generator,
        std::unique_ptr<dorm_energy::detection::IAnomalyDetector> detector,
        std::shared_ptr<dorm_energy::storage::IMeasurementRepository> repository)
        : logger_(std::move(logger)), generator_(std::move(generator)), detector_(std::move(detector)), repository_(std::move(repository))
    {
        if (!logger_ || !generator_ || !detector_ || !repository_)
        {
            throw std::invalid_argument("SimulateCommand: all dependencies must be provided");
        }
    }

    int SimulateCommand::execute(const cli::CommandOptions &options)
    {
        logger_->info("Starting simulation for " + std::to_string(options.simulateDays) + " days");

        if (options.injectAnomalies)
        {
            logger_->info("Anomaly injection mode enabled");
        }

        core::ReadingsBatch batch = generator_->generate_for_days(options.simulateDays);

        logger_->info("Generated " + std::to_string(batch.size()) + " sensor readings");

        int anomalyCount = detector_->countAnomalies(batch);
        logger_->info("Detected anomalies: " + std::to_string(anomalyCount));

        if (anomalyCount > 0)
        {
            auto anomalies = detector_->getAnomalies(batch);
            std::cout << "\n=== ANOMALIES DETECTED ===\n";
            for (const auto &anomaly : anomalies)
            {
                std::cout << core::toString(anomaly) << std::endl;
            }
        }

        std::size_t saved = repository_->saveBatch(batch);
        logger_->info("Saved " + std::to_string(saved) + " readings to the database");

        logger_->info("Simulation completed successfully");
        return 0;
    }

} // namespace dorm_energy::application