# ESP-IDF component manifest for M5HAL.
# Upstream: https://github.com/m5stack/M5HAL (HAL abstraction; Arduino impl
# is conditional on __has_include(<Arduino.h>) and #if defined(ARDUINO)).
# Under pure ESP-IDF, the native GPIO impl (gpio.inl) bit-bangs via
# driver/gpio.h, so the GPIO driver component is required to build M5HAL.cpp.
# It is private because the public header (gpio.hpp) does not expose
# driver/gpio.h.
#
# esp_driver_gpio was split out of the monolithic 'driver' component in IDF
# v5.2. On v5.0/v5.1 the GPIO driver (driver/gpio.h) lives in 'driver'.
if("${IDF_VERSION_MAJOR}.${IDF_VERSION_MINOR}" VERSION_GREATER_EQUAL "5.2")
    set(m5hal_gpio_req esp_driver_gpio)
else()
    set(m5hal_gpio_req driver)
endif()

idf_component_register(
    SRCS "src/M5HAL.cpp"
    INCLUDE_DIRS "src"
    REQUIRES M5Utility
    PRIV_REQUIRES ${m5hal_gpio_req}
)
