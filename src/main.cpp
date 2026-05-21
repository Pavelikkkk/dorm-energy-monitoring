// src/main.cpp
#include "dorm_energy/application/application.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    try
    {
        dorm_energy::application::Application app;
        return app.run(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << "[FATAL] Необработанное исключение: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "[FATAL] Неизвестная ошибка" << std::endl;
        return 1;
    }
}