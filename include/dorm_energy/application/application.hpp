// include/dorm_energy/application/application.hpp
#pragma once

#include "dorm_energy/infrastructure/cli/cli_parser.hpp"
#include "dorm_energy/application/commands/simulate_command.hpp"
#include "dorm_energy/application/commands/daemon_command.hpp"

#include <memory>

namespace dorm_energy::application
{

    /**
     * @brief Главный класс приложения.
     *
     * Теперь он очень тонкий и отвечает только за:
     * 1. Запуск парсинга командной строки
     * 2. Выбор и запуск нужной команды
     */
    class Application
    {
    public:
        /**
         * @brief Конструктор принимает уже готовые команды
         */
        explicit Application(
            std::unique_ptr<dorm_energy::cli::CliParser> cliParser,
            std::unique_ptr<dorm_energy::application::SimulateCommand> simulateCommand,
            std::unique_ptr<dorm_energy::application::DaemonCommand> daemonCommand);

        ~Application() = default;

        /**
         * @brief Главная точка входа в приложение
         * @return код завершения программы (0 = успех)
         */
        int run(int argc, char **argv);

    private:
        std::unique_ptr<dorm_energy::cli::CliParser> cliParser_;
        std::unique_ptr<dorm_energy::application::SimulateCommand> simulateCommand_;
        std::unique_ptr<dorm_energy::application::DaemonCommand> daemonCommand_;
    };

} // namespace dorm_energy::application