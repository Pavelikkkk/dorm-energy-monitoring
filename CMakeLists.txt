cmake_minimum_required(VERSION 3.23)

project(dorm-energy-sim
    VERSION 0.0.0
    DESCRIPTION "Мониторинг энергопотребления в общежитии"
    LANGUAGES CXX
)

add_executable(Diplome)

target_sources(Diplome
  PRIVATE
    src/main.cpp)

