cmake_minimum_required(VERSION 3.23)

project(dorm-energy-sim
    VERSION 0.0.0
    DESCRIPTION "Имитация и мониторинг энергопотребления в общежитии"
    LANGUAGES CXX
)
add_subdirectory(external/CLI11)

add_executable(Diplome)

target_sources(Diplome
  PRIVATE
    src/main.cpp
)

target_link_libraries(Diplome 
  PRIVATE 
    CLI11::CLI11
)
