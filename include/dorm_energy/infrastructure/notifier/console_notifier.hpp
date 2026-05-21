// include/dorm_energy/infrastructure/notifier/console_notifier.hpp
#pragma once

#include "dorm_energy/application/inotifier.hpp"
#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::infrastructure::notifier
{

    /**
     * @brief Реализация уведомлений в консоль
     */
    class ConsoleNotifier : public application::INotifier
    {
    public:
        ConsoleNotifier() = default;

        void sendAlert(const core::SensorReading &reading,
                        const std::string &reason = "") override;

        void sendAlerts(const std::vector<core::SensorReading> &readings,
                         const std::string &reason = "") override;

    private:
        std::string formatAlert(const core::SensorReading &reading,
                                const std::string &reason) const;
    };

} // namespace dorm_energy::infrastructure::notifier