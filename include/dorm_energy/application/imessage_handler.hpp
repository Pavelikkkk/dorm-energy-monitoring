// include/dorm_energy/domain/mqtt/imessage_handler.hpp
#pragma once

#include "dorm_energy/core/measurement.hpp"

namespace dorm_energy::application
{

    /**
     * @brief Интерфейс для обработки входящих сообщений от датчиков (MQTT)
     */
    class IMessageHandler
    {
    public:
        virtual ~IMessageHandler() = default;

        /**
         * @brief Обрабатывает одно новое показание от датчика
         * @param reading полученное показание
         */
        virtual void handle(const core::SensorReading &reading) = 0;

        /**
         * @brief Принудительно сбрасывает накопленный батч (например, при остановке)
         */
        virtual void flush() = 0;
    };

} // namespace dorm_energy::application