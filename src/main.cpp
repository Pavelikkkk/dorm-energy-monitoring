#include <iostream>

int main(int args, char* argv[]){

    std::cout << "Dorm Energy Simulator\n";
    std::cout << "iteration 1 - Skeleton\n";

    if(args > 1){
        std::string arg = argv[1];
        if(arg == "--version" || arg == "-v"){
            std::cout << "version 0.0.1-dev";
            return 0;  
        }
    }

    std::cout << "usage:\n";
    std::cout << "sim --version\n";
    std::cout << "Enter....\n";
    std::cin.get();   
    return 1;
}