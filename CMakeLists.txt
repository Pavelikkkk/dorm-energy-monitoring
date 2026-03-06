cmake_minimum_required(VERSION 3.23)

project(dorm-energy-sim
    VERSION 1.1
    DESCRIPTION "Имитация и мониторинг энергопотребления в общежитии"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build unit tests" ON)

add_subdirectory(external/CLI11)

add_executable(dorm-sim)

target_sources(dorm-sim
  PRIVATE
    src/main.cpp
)

target_link_libraries(dorm-sim 
  PRIVATE 
    CLI11::CLI11
)

if(BUILD_TESTING)
    enable_testing()
    message(STATUS "Тестирование включено (BUILD_TESTING=ON)")

    add_executable(test_cli tests/test_cli.cpp)
    target_link_libraries(test_cli PRIVATE CLI11::CLI11)

endif()
