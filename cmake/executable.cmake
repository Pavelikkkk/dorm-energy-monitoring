# ============================================
# Основное приложение
# ============================================

add_executable(dorm-sim
    src/main.cpp
)

add_custom_command(
    TARGET dorm-sim
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ONNXRUNTIME_ROOT}/lib/onnxruntime.dll"
        "$<TARGET_FILE_DIR:dorm-sim>/onnxruntime.dll"
)

add_custom_command(
    TARGET dorm-sim
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ONNXRUNTIME_ROOT}/lib/onnxruntime_providers_shared.dll"
        "$<TARGET_FILE_DIR:dorm-sim>/onnxruntime_providers_shared.dll"
)

target_include_directories(dorm_energy_core
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(dorm-sim 
    PRIVATE 
        dorm_energy_core
)
