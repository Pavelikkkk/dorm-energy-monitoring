#include "dorm_energy/infrastructure/handlers/message_handler.hpp"

#include <fmt/format.h>
#include <iostream>

namespace dorm_energy::handlers
{

    MessageHandler::MessageHandler(
        std::unique_ptr<dorm_energy::detection::IStateDetector> detector,
        std::shared_ptr<dorm_energy::storage::IMeasurementRepository> repository,
        std::unique_ptr<dorm_energy::application::INotifier> notifier)
        : detector_(std::move(detector)),
          repository_(std::move(repository)),
          notifier_(std::move(notifier))
    {
        if (!detector_ || !repository_ || !notifier_)
        {
            throw std::invalid_argument(
                "MessageHandler: all dependencies must be provided");
        }
    }

    bool MessageHandler::handle(
        const core::SensorReading &reading)
    {
        batch_.push_back(reading);

        constexpr std::size_t
            BATCH_THRESHOLD = 100;

        if (batch_.size() >= BATCH_THRESHOLD)
        {
            persistCurrentBatch();
        }

        auto state =
            aggregator_.update(reading);

        if (!state.has_value())
        {
            return true;
        }

        auto anomalyInfo =
            detector_->detect(*state);

        if (anomalyInfo.isAnomaly)
        {
            repository_->saveAnomaly(
                reading,
                anomalyInfo.anomalyType,
                anomalyInfo.severity,
                anomalyInfo.description);

            notifier_->sendAlert(
                reading,
                anomalyInfo.severity,
                anomalyInfo.description);
        }

        return true;
    }

    std::size_t MessageHandler::handleBatch(
        const std::vector<core::SensorReading> &readings)
    {
        if (readings.empty())
            return 0;

        std::size_t processed = 0;

        for (const auto &reading : readings)
        {
            handle(reading);
            ++processed;
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

        std::size_t saved =
            repository_->saveBatch(batch_);

        std::cout
            << fmt::format(
                   "[MessageHandler] Saved {} readings to repository (batch size: {})\n",
                   saved,
                   batch_.size());

        batch_.clear();
    }

} // namespace dorm_energy::handlers