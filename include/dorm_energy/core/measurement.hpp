// include/dorm_energy/core/measurement.hpp
#pragma once

#include <chrono>
#include <vector>
#include <string>
#include <optional>

namespace dorm_energy::core
{
    /**
     * @brief Универсальное показание с любого датчика
     *
     * Это основная единица данных всего проекта.
     */
    struct SensorReading
    {
        using TimePoint = std::chrono::system_clock::time_point;

        TimePoint timestamp{};    ///< Время измерения
        std::string deviceId{};   ///< Идентификатор устройства/датчика
        std::string sensorType{}; ///< "power", "motion", "light", "temperature" и т.д.

        double value{0.0};               ///< Используется для числовых датчиков (power, temp, lux)
        std::optional<bool> boolValue{}; ///< Используется для булевых датчиков (motion)

        std::string unit{}; ///< "kW", "bool", "lux", "°C" и т.д.

        SensorReading() = default;

        SensorReading(TimePoint ts,
                      std::string device,
                      std::string type,
                      double val = 0.0,
                      std::optional<bool> bval = std::nullopt,
                      std::string u = "")
            : timestamp{ts},
              deviceId{std::move(device)},
              sensorType{std::move(type)},
              value{val},
              boolValue{bval},
              unit{std::move(u)}
        {
        }
    };

    /**
     * @brief Основной тип для работы с коллекциями показаний
     */
    using ReadingsBatch = std::vector<SensorReading>;

    /**
     * @brief Получить час дня (0-23) из timestamp
     */
    int getHourOfDay(const SensorReading &reading);

    /**
     * @brief Красивое строковое представление для логов
     */
    std::string toString(const SensorReading &reading);

    /**
     * @brief Преобразование в JSON (для MQTT)
     */
    std::string toJson(const SensorReading &reading); // возможно вынести

} // namespace dorm_energy::core