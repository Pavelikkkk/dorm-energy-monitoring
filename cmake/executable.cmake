# ============================================
# Основное приложение
# ============================================

add_executable(dorm-sim
    src/main.cpp
)

target_include_directories(dorm_energy_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(dorm-sim 
    PRIVATE 
        dorm_energy_core
)
