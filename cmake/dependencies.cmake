# ============================================
# Зависимости (vcpkg)
# ============================================

find_package(CLI11 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PahoMqttCpp CONFIG REQUIRED)
# find_package(eclipse-paho-mqtt-c CONFIG REQUIRED)
# find_package(paho-mqttpp3 CONFIG QUIET)