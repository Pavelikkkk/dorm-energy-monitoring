// src/dorm_energy/infrastructure/handlers/message_handler.cpp
#include "dorm_energy/infrastructure/handlers/message_handler.hpp"

#include <fmt/format.h>
#include <iostream>

namespace dorm_energy::handlers
{

    MessageHandler::MessageHandler(
        std::unique_ptr<dorm_energy::detection::IAnomalyDetector> detector,
        std::shared_ptr<dorm_energy::storage::IMeasurementRepository> repository,
        std::unique_ptr<dorm_energy::application::INotifier> notifier)
        : detector_(std::move(detector)),
          repository_(std::move(repository)),
          notifier_(std::move(notifier))
    {
        if (!detector_ || !repository_ || !notifier_)
        {
            throw std::invalid_argument("MessageHandler: all dependencies must be provided");
        }
    }

    bool MessageHandler::handle(const core::SensorReading &reading)
    {
        auto anomalyInfo = detector_->detect(reading);

        if (anomalyInfo.isAnomaly)
        {
            processAnomaly(reading);
            notifier_->sendAlert(reading, anomalyInfo.description);
        }

        batch_.push_back(reading);

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

        for (const auto &reading : readings)
        {
            auto anomalyInfo = detector_->detect(reading);

            if (anomalyInfo.isAnomaly)
            {
                processAnomaly(reading);
                notifier_->sendAlert(reading, anomalyInfo.description);
            }

            batch_.push_back(reading);
            ++processed;
        }

        const std::size_t BATCH_THRESHOLD = 100;
        if (batch_.size() >= BATCH_THRESHOLD)
        {
            persistCurrentBatch();
        }

        return processed;
    }

    void MessageHandler::processAnomaly(const core::SensorReading &reading)
    {
        auto info = detector_->detect(reading);

        repository_->saveAnomaly(
            reading,
            info.anomalyType,
            info.severity,
            info.description);
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

        std::cout << fmt::format("[MessageHandler] Saved {} readings to repository (batch size: {})\n",
                                 saved, batch_.size());

        batch_.clear();
    }

} // namespace dorm_energy::handlers