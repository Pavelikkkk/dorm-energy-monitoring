// include/dorm_energy/infrastructure/handlers/message_handler.hpp
#pragma once

#include "dorm_energy/application/imessage_handler.hpp"
#include "dorm_energy/domain/detection/ianomaly_detector.hpp"
#include "dorm_energy/domain/storage/imeasurement_repository.hpp"
#include "dorm_energy/application/inotifier.hpp"
#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::infrastructure::handlers
{

    /**
     * @brief Основная реализация обработчика входящих сообщений
     *
     * Оркестрирует весь цикл обработки одного показания:
     * 1. Детекция аномалий
     * 2. Сохранение в репозиторий
     * 3. Отправка уведомлений (если аномалия)
     */
    class MessageHandler : public application::IMessageHandler
    {
    public:
        explicit MessageHandler(
            std::unique_ptr<domain::detection::IAnomalyDetector> detector,
            std::unique_ptr<domain::storage::IMeasurementRepository> repository,
            std::unique_ptr<application::INotifier> notifier);

        void handle(const core::SensorReading &reading) override;

        void flush() override;

    private:
        std::unique_ptr<domain::detection::IAnomalyDetector> detector_;
        std::unique_ptr<domain::storage::IMeasurementRepository> repository_;
        std::unique_ptr<application::INotifier> notifier_;

        // Можно добавить накопление батча для производительности
        core::ReadingsBatch batch_;
    };

} // namespace dorm_energy::infrastructure::handlers