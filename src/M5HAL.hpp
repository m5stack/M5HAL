#ifndef M5_HAL_HPP
#define M5_HAL_HPP

#include <M5Utility.hpp>

#include "./m5_hal/platform_checker.hpp"
#include "./m5_hal/framework_checker.hpp"
#include "./m5_hal/bus/i2c.hpp"
#include "./m5_hal/bus/spi.hpp"

#include "./m5_hal/bus/bus.hpp"
#include "./m5_hal/interface/gpio.hpp"

#define M5HAL_STATIC_MACRO_STRING(x) #x
// clang-format off
#define M5HAL_STATIC_MACRO_CONCAT(x, y) M5HAL_STATIC_MACRO_STRING(x/y)
// clang-format on

#define M5HAL_STATIC_MACRO_PATH_HEADER M5HAL_STATIC_MACRO_CONCAT(M5HAL_TARGET_PLATFORM_PATH, header.hpp)

#if M5HAL_TARGET_PLATFORM_NUMBER != 0
#include M5HAL_STATIC_MACRO_PATH_HEADER
#endif

#undef M5HAL_STATIC_MACRO_PATH_HEADER

// Arduinoフレームワークがある場合は準備
#if M5HAL_FRAMEWORK_HAS_ARDUINO
#include "./m5_hal/frameworks/arduino/header.hpp"

// Arduino 搭載時は Arduino 経由の実装を利用
namespace m5 {
namespace hal {
using namespace frameworks::arduino;
}
}  // namespace m5

#elif M5HAL_TARGET_PLATFORM_NUMBER != 0

// Arduino 非搭載 (pure ESP-IDF) かつ platform 既知時は native 実装を利用。
// platforms::esp32 全体を using namespace すると、esp32 (初代) header が持つ
// 入れ子の platforms::esp32::types が m5::hal::types と衝突するため、必要な
// gpio 自由関数だけを m5::hal::gpio へ取り込む。
namespace m5 {
namespace hal {
namespace gpio {
using platforms::esp32::gpio::getGPIO;
using platforms::esp32::gpio::getPin;
}  // namespace gpio
}  // namespace hal
}  // namespace m5

#endif

#endif
