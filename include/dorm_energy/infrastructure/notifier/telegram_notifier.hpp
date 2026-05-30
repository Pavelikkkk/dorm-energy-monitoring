#pragma once

#include "dorm_energy/application/inotifier.hpp"
#include "telegram_config.hpp"
#include "telegram_queue.hpp"
#include "telegram_poller.hpp"
#include <atomic>
#include <thread>
#include <chrono>

namespace dorm_energy::notifier
{
    class TelegramNotifier : public application::INotifier
    {
    public:
        explicit TelegramNotifier(const application::AppConfig &config);
        explicit TelegramNotifier(TelegramConfig cfg);
        ~TelegramNotifier();

        bool sendAlert(const core::SensorReading &reading,
                       core::AlertSeverity severity = core::AlertSeverity::Warning,
                       const std::string &reason = "") override;

        std::size_t sendAlerts(const std::vector<core::SensorReading> &readings,
                               core::AlertSeverity severity = core::AlertSeverity::Warning,
                               const std::string &reason = "") override;

    private:
        TelegramConfig config_;
        std::string apiUrl_;
        TelegramQueue queue_;
        TelegramPoller poller_;

        std::thread workerThread_;
        std::atomic<bool> running_{false};
        std::atomic<std::chrono::seconds> currentBackoff_{std::chrono::seconds{5}};

        bool sendMessage(const std::string &text);
        std::string buildAlertMessage(const core::SensorReading &reading,
                                      core::AlertSeverity severity,
                                      const std::string &reason) const;

        void startQueueWorker();
        void stopQueueWorker();
        void queueWorker();
        bool flushQueue();
        void logQueueStatus();
    };
}