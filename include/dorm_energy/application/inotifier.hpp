// include/dorm_energy/application/inotifier.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"
#include <string>

namespace dorm_energy::application
{
    /**
     * @brief Порт для отправки уведомлений об аномалиях
     *
     * Реализации могут быть:
     * - ConsoleNotifier
     * - TelegramNotifier
     * - EmailNotifier
     * - Push-уведомления и т.д.
     */
    class INotifier
    {
    public:
        virtual ~INotifier() = default;

        /**
         * @brief Отправляет alert об аномальном показании
         * @param reading аномальное показание
         * @param reason  причина, почему это аномалия (опционально)
         */
        virtual void sendAlert(const core::SensorReading &reading,
                                const std::string &reason = "") = 0;

        /**
         * @brief Отправляет несколько алертов за раз (например, при обнаружении нескольких аномалий в батче)
         * @param readings вектор аномальных показаний
         * @param reason  причина, почему это аномалия (опционально)
         */
        virtual void sendAlerts(const std::vector<core::SensorReading> &readings,
                                 const std::string &reason = "") = 0;
    };

} // namespace dorm_energy::application