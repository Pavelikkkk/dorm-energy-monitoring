// include/dorm_energy/infrastructure/logging/spdlog_logger.hpp
#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "dorm_energy/domain/logging/ilogger.hpp"

namespace dorm_energy::infrastructure::logging
{

    class SpdlogLogger : public domain::logging::ILogger
    {
    public:
        SpdlogLogger(const std::string &name = "dorm-energy");

        void log(domain::logging::LogLevel level, const std::string &message) override;

    private:
        std::shared_ptr<spdlog::logger> logger_;
    };

} // namespace dorm_energy::infrastructure::logging