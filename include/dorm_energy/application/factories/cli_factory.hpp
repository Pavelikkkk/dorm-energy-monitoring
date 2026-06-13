#pragma once

#include <memory>

namespace dorm_energy::cli
{
    class CliParser;
}

namespace dorm_energy::application::factories
{
    class CliFactory
    {
    public:
        std::unique_ptr<cli::CliParser> createParser() const;
    };
} // namespace dorm_energy::application::factories
