// main.cpp
// ────────────────────────────────────────────────────────────────
// Dorm Energy Simulator — CLI entry point
// C++20 console application for energy consumption simulation
// Parses command-line arguments using CLI11
// Supports: --version, simulate subcommand with --days, --output, --verbose
// ────────────────────────────────────────────────────────────────

#include <iostream>
#include <string>
#include <string_view>
#include <format>           
#include <CLI/CLI.hpp> 

void print_version() noexcept {
    std::cout << std::format("Dorm Energy Simulator\n"
                             "Version: 1.1\n"
                             "Author: Pasha\n",
                             __DATE__);
}

void run_simulation(int days, std::string_view output_file, bool verbose) {
    std::cout << "Starting simulation:\n"
              << std::format("  Days:           {}\n", days)
              << std::format("  Output file:    {}\n", output_file);

    if (verbose) {
        std::cout << "  Verbose mode:   enabled\n";
    }

    std::cout << std::format("Simulation in progress... (generating {} days of data)\n", days);
    std::cout << std::format("Results saved to {}\n", output_file);
}


int main(int argc, char* argv[]){
    // ────────────────────────────────────────────────────────────────
    // Application setup
    // ────────────────────────────────────────────────────────────────

    CLI::App app{"Dorm Energy Simulator — Energy consumption simulation and monitoring in a student dormitory"};
    
    bool version_flag{false};
    app.add_flag("--version, -v", version_flag, "Show version");

    // ────────────────────────────────────────────────────────────────
    // Subcommand: simulate
    // ────────────────────────────────────────────────────────────────
    auto* sim = app.add_subcommand("simulate", "Run energy consumption simulation");  

    int days{30}; // default 
    sim->add_option("--days,-d", days, "Simulation days")
            ->default_val(30)
            ->check(CLI::Range(1, 365, "days"))
            ->required(false);

    std::string output_file{"result.csv"};
    sim->add_option("--output,-o", output_file, "Save results")
       ->default_val("result.csv");

    bool verbose{false};
    sim->add_flag("--verbose,-v", verbose, "Logs");   
    
    // ────────────────────────────────────────────────────────────────
    // Parse arguments
    // ────────────────────────────────────────────────────────────────

    try {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e) {
        return app.exit(e);
    }
    
    // ────────────────────────────────────────────────────────────────
    // Business logic — narrow scopes
    // ────────────────────────────────────────────────────────────────

    if(version_flag){
        print_version();
        return 0;
    }

    if(sim->parsed()){
        run_simulation(days, output_file, verbose);
        return 0;
    }

    std::cerr << "No command provided.\n\n";
    std::cout << app.help() << "\n";
    
    return 1;
}