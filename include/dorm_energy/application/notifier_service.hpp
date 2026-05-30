#pragma once

#include "dorm_energy/application/inotifier.hpp"
#include <vector>
#include <memory>

namespace dorm_energy::application
{
    /**
     * @brief Композитный нотификатор — позволяет использовать несколько каналов одновременно
     * (Console + Telegram + WebSocket и т.д.)
     */
    class NotifierService : public INotifier
    {
    public:
        NotifierService() = default;

        void addNotifier(std::unique_ptr<INotifier> notifier);

        bool sendAlert(const core::SensorReading &reading,
                       core::AlertSeverity severity = core::AlertSeverity::Warning,
                       const std::string &reason = "") override;

        std::size_t sendAlerts(const std::vector<core::SensorReading> &readings,
                               core::AlertSeverity severity = core::AlertSeverity::Warning,
                               const std::string &reason = "") override;

    private:
        std::vector<std::unique_ptr<INotifier>> notifiers_;
    };
}