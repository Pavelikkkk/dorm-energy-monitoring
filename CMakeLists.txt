cmake_minimum_required(VERSION 3.23)

project(dorm-energy-sim
    VERSION 1.1
    DESCRIPTION "Имитация и мониторинг энергопотребления в общежитии"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build unit tests" OFF)

add_subdirectory(external/CLI11)

set(SIM_SOURCES
    src/simulator.cpp         
    src/anomaly_detector.cpp
    src/csv_writer.cpp
)

# ============================================
# ОСНОВНАЯ ПРОГРАММА
# ============================================

add_executable(dorm-sim
    src/main.cpp
    ${SIM_SOURCES}
)

target_link_libraries(dorm-sim 
  PRIVATE 
    CLI11::CLI11
)

function(enable_sanitizers TARGET_NAME)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${TARGET_NAME} PRIVATE 
            -fsanitize=address,undefined 
            -g 
            -O1 
            -fno-omit-frame-pointer
        )
        target_link_options(${TARGET_NAME} PRIVATE 
            -fsanitize=address,undefined
        )
        message(STATUS "Sanitizers enabled for ${TARGET_NAME}")
    endif()
endfunction()

enable_sanitizers(dorm-sim)

# ============================================
# ТЕСТЫ
# ============================================

if(BUILD_TESTING)
    enable_testing()
    message(STATUS "Тестирование включено (BUILD_TESTING=ON)")

    add_executable(test_cli tests/test_cli.cpp
    src/simulator.cpp         
    src/anomaly_detector.cpp
    src/csv_writer.cpp
)
    target_link_libraries(test_cli PRIVATE CLI11::CLI11)

endif()


