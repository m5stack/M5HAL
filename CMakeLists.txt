# ESP-IDF component manifest for M5HAL.
# Upstream: https://github.com/m5stack/M5HAL (HAL abstraction; Arduino impl
# is conditional on __has_include(<Arduino.h>) and #if defined(ARDUINO),
# so under pure ESP-IDF the file compiles to empty implementations).
idf_component_register(
    SRCS "src/M5HAL.cpp"
    INCLUDE_DIRS "src"
    REQUIRES M5Utility
)
