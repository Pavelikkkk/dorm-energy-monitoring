// src/dorm_energy/application/config/app_config.cpp
#include "dorm_energy/application/config/app_config.hpp"
#include "dorm_energy/application/cli/command_options.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <filesystem>

namespace dorm_energy::application
{
    AppConfig AppConfig::load()
    {
        AppConfig config = loadFromEnvFile(".env");

        AppConfig envConfig = loadFromEnvironment();

        if (!envConfig.dbHost.empty())
            config.dbHost = envConfig.dbHost;
        if (!envConfig.dbPort.empty())
            config.dbPort = envConfig.dbPort;
        if (!envConfig.dbName.empty())
            config.dbName = envConfig.dbName;
        if (!envConfig.dbUser.empty())
            config.dbUser = envConfig.dbUser;
        if (!envConfig.dbPassword.empty())
            config.dbPassword = envConfig.dbPassword;
        return config;
    }

    AppConfig AppConfig::loadFromEnvFile(const std::string &filename)
    {
        AppConfig config;

        std::filesystem::path exePath;
        try
        {
            exePath = std::filesystem::current_path() / filename;

            if (!std::filesystem::exists(exePath))
            {
                auto parentPath = std::filesystem::current_path().parent_path();
                if (parentPath.filename() == "build" || parentPath.filename() == "Debug" || parentPath.filename() == "Release")
                {
                    exePath = parentPath.parent_path() / filename;
                }
            }
        }
        catch (...)
        {
            exePath = filename;
        }

        std::ifstream file(exePath);
        if (!file.is_open())
        {
            std::cout << "[Config] .env file not found\n";
            return config;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            auto pos = line.find('=');
            if (pos == std::string::npos)
                continue;

            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);

            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            if (key == "DB_HOST")
                config.dbHost = value;
            else if (key == "DB_PORT")
                config.dbPort = value;
            else if (key == "DB_NAME")
                config.dbName = value;
            else if (key == "DB_USER")
                config.dbUser = value;
            else if (key == "DB_PASSWORD")
                config.dbPassword = value;
            else if (key == "MQTT_BROKER")
                config.mqttBroker = value;
            else if (key == "LOG_LEVEL")
                config.logLevel = value;
            else if (key == "SIMULATION_DAYS")
            {
                try
                {
                    config.simulationDays = std::stoi(value);
                }
                catch (...)
                {
                }
            }
        }
        return config;
    }

    AppConfig AppConfig::loadFromEnvironment()
    {
        AppConfig config;

        if (const char *val = std::getenv("MQTT_BROKER"))
            config.mqttBroker = val;
        if (const char *val = std::getenv("MQTT_TOPIC"))
            config.mqttTopic = val;
        if (const char *val = std::getenv("DB_HOST"))
            config.dbHost = val;
        if (const char *val = std::getenv("DB_PORT"))
            config.dbPort = val;
        if (const char *val = std::getenv("DB_NAME"))
            config.dbName = val;
        if (const char *val = std::getenv("DB_USER"))
            config.dbUser = val;
        if (const char *val = std::getenv("DB_PASSWORD"))
            config.dbPassword = val;
        if (const char *val = std::getenv("LOG_LEVEL"))
            config.logLevel = val;

        if (const char *val = std::getenv("SIMULATION_DAYS"))
        {
            try
            {
                config.simulationDays = std::stoi(val);
            }
            catch (...)
            {
            }
        }
        return config;
    }

    void AppConfig::overrideFromCli(const cli::CommandOptions &cli)
    {
        if (cli.common.verbose)
            verbose = true;

        if (cli.isSimulate())
        {
            simulationDays = cli.simulateDays;
            injectAnomalies = cli.injectAnomalies;
            anomalyRate = cli.anomalyRate;
        }

        if (!cli.mqttBroker.empty())
            mqttBroker = cli.mqttBroker;
        if (!cli.mqttTopic.empty())
            mqttTopic = cli.mqttTopic;
    }

    std::string AppConfig::getDbConnectionString() const
    {
        std::ostringstream oss;
        oss << "host=" << dbHost
            << " port=" << dbPort
            << " dbname=" << dbName
            << " user=" << dbUser;

        if (!dbPassword.empty())
            oss << " password=" << dbPassword;

        return oss.str();
    }

    std::string AppConfig::validate() const
    {
        if (mqttBroker.empty())
            return "MQTT broker address is not set";
        if (dbHost.empty() || dbName.empty())
            return "Database configuration is incomplete";
        if (simulationDays <= 0)
            return "Simulation days must be positive";
        return "";
    }

    void AppConfig::clearSensitiveData()
    {
        dbPassword.clear();
        dbPassword.shrink_to_fit();
    }

} // namespace dorm_energy::application