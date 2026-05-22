// include/dorm_energy/application/cli/command_options.hpp
#pragma once

#include "command_type.hpp"

#include <string>

namespace dorm_energy::cli
{

    /**
     * @brief Общие параметры для всех команд
     */
    struct CommonOptions
    {
        bool verbose{false};
        bool help{false};
    };

    struct SimulateOptions
    {
        int days{30};
        unsigned seed{42};
        bool inject_anomalies{false};
        double anomaly_rate{0.03};
    };

    struct DaemonOptions
    {
        std::string mqttBroker{"tcp://127.0.0.1:1883"}; // подумать над дефолтами
        std::string mqttClientId{"dorm-energy"};
        std::string mqttTopic{"devices/+/power"};
    };

    /**
     * @brief Основная структура с результатами парсинга
     */
    struct CommandOptions
    {
        CommandType type{CommandType::Unknown};

        CommonOptions common;
        SimulateOptions simulate;
        DaemonOptions daemon;

        bool isSimulate() const noexcept { return type == CommandType::Simulate; }
        bool isDaemon() const noexcept { return type == CommandType::Daemon; }
        bool isHelp() const noexcept { return type == CommandType::Help; }
    };

} // namespace dorm_energy::application::cli