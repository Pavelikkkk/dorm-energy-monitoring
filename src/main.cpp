#include <iostream>
#include <string>
#include "D:\programmingThings\Projects\diaplome\dorm-energy-sim\external\CLI11\include\CLI\CLI.hpp"

// void print_usage(){
//     std::cout << "Dorm Energy Simulator - usage:\n";
//     std::cout << "  sim --version, -v     show version\n";
//     std::cout << "  sim --help, -h        show help menu\n";
//     std::cout << "  sim simulate          soon\n";
// }


int main(int argc, char* argv[]){

    CLI::App app{"Dorm Energy Simulator — Energy consumption simulation and monitoring in a student dormitory"};
    
    bool show_version{false};
    app.add_flag("--version, -v", show_version, "Show version");

    auto simulate = app.add_subcommand("simulate", "Run imitation");

    int days{30}; // default 

    simulate->add_option("--days,-d", days, "Simulation days")
            ->default_val(30)
            ->check(CLI::Range(1, 365, "days"));

    std::string output_file{"result.csv"};

    simulate->add_option("--output,-o", output_file, "Файл для сохранения результатов")
       ->default_val("result.csv");

    bool verbose{false};

    simulate->add_flag("--verbose,-v", verbose, "Подробный вывод (логи, промежуточные данные)");   
    
    CLI11_PARSE(app, argc, argv);
    
    if(show_version){
        std::cout << "Dorm Energy Simulator version 0.0.1-dev\n";
        return 0;
    }

    if(simulate->parsed()){
        std::cout << "Запуск симуляции:\n";
        std::cout << "  Дней:           " << days << "\n";
        std::cout << "  Выходной файл:  " << output_file << "\n";
        if (verbose) {
            std::cout << "  Подробный режим: включён\n";
        }

        std::cout << "Имитация запущена... (данные генерируются)\n";
        std::cout << "Результат сохранён в " << output_file << "\n";

        return 0;
    }

    std::cerr << "Команда не указана. Попробуйте:\n";
    std::cerr << "  sim --version\n";
    std::cerr << "  sim simulate --help\n";
    
    return 1;
}