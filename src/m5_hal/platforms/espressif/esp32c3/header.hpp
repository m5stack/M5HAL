#ifndef M5_HAL_PLATFORMS_ESPRESSIF_ESP32C3_HEADER_HPP
#define M5_HAL_PLATFORMS_ESPRESSIF_ESP32C3_HEADER_HPP

#include "../../../interface/gpio.hpp"
#include "../gpio.hpp"

namespace m5 {
namespace hal {
namespace platforms {
namespace esp32 {
namespace gpio {
interface::gpio::GPIO* getGPIO(void);
}  // namespace gpio
}  // namespace esp32
}  // namespace platforms
}  // namespace hal
}  // namespace m5

#endif
