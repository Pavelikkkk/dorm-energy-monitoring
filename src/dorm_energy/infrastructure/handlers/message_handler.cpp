// src/dorm_energy/infrastructure/handlers/message_handler.cpp
#include "dorm_energy/infrastructure/handlers/message_handler.hpp"

#include <iostream>

namespace dorm_energy::handlers
{

    MessageHandler::MessageHandler(
        std::unique_ptr<dorm_energy::detection::IAnomalyDetector> detector,
        std::shared_ptr<dorm_energy::storage::IMeasurementRepository> repository,
        std::unique_ptr<dorm_energy::application::INotifier> notifier)
        : detector_(std::move(detector)), repository_(std::move(repository)), notifier_(std::move(notifier))
    {
        if (!detector_ || !repository_ || !notifier_)
        {
            throw std::invalid_argument("MessageHandler: all dependencies must be provided");
        }
    }

    bool MessageHandler::handle(const core::SensorReading &reading)
    {
        if (detector_->isAnomaly(reading))
        {
            notifier_->sendAlert(reading, "Power consumption anomaly detected");
        }

        batch_.push_back(reading);
        
        // пока простой порогпотом сделатьнорм
        const std::size_t BATCH_THRESHOLD = 100;
        if (batch_.size() >= BATCH_THRESHOLD)
        {
            persistCurrentBatch();
        }

        return true;
    }

    std::size_t MessageHandler::handleBatch(const std::vector<core::SensorReading> &readings)
    {
        if (readings.empty())
            return 0;

        std::size_t processed = 0;
        std::vector<core::SensorReading> anomalies;

        for (const auto &reading : readings)
        {
            if (detector_->isAnomaly(reading))
            {
                anomalies.push_back(reading);
            }

            batch_.push_back(reading);
            ++processed;
        }

        if (!anomalies.empty())
        {
            notifier_->sendAlerts(anomalies, "Multiple anomalies detected in batch");
        }

        const std::size_t BATCH_THRESHOLD = 100;
        if (batch_.size() >= BATCH_THRESHOLD)
        {
            persistCurrentBatch();
        }

        return processed;
    }

    void MessageHandler::flush()
    {
        persistCurrentBatch();
    }

    void MessageHandler::persistCurrentBatch()
    {
        if (batch_.empty())
            return;

        std::size_t saved = repository_->saveBatch(batch_);

        // TODO: заменить на ILogger позже
        std::cout << "[MessageHandler] Saved " << saved
                  << " readings to repository (batch size: " << batch_.size() << ")\n";

        batch_.clear();
    }

} // namespace dorm_energy::handlers