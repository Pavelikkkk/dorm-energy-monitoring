// include/dorm_energy/infrastructure/cli/cli_parser.hpp
#pragma once

#include "dorm_energy/application/cli/command_options.hpp"

#include <CLI/CLI.hpp>

#include <memory>

namespace dorm_energy::cli
{

    enum class ParseResult
    {
        Continue,
        ExitSuccess,
        ExitError
    };

    class CliParser
    {
    public:
        CliParser();

        ParseResult parse(int argc, char **argv, CommandOptions &options);

    private:
        void setupCommands();
        std::unique_ptr<CLI::App> app_;
    };

} // namespace dorm_energy::cli