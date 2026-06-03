#ifndef M5_HAL_PLATFORMS_ESPRESSIF_GPIO_HPP
#define M5_HAL_PLATFORMS_ESPRESSIF_GPIO_HPP

#include "../../interface/gpio.hpp"

#if defined(ESP_PLATFORM) && !defined(ARDUINO)

namespace m5 {
namespace hal {
namespace platforms {
namespace esp32 {
namespace gpio {

// ESP-IDF GPIO driver ベースの単一デジタルピン
class Pin : public interface::gpio::Pin {
public:
    void write(bool value) override;
    void writeHigh(void) override;
    void writeLow(void) override;
    bool read(void) override;

    void setMode(m5::hal::types::gpio_mode_t mode) override;
    m5::hal::types::gpio_number_t getGpioNumber(void) const override
    {
        return _gpio_number;
    }

    Pin(void) = default;
    Pin(m5::hal::types::gpio_number_t gpio_number) : _gpio_number{gpio_number}
    {
    }

protected:
    m5::hal::types::gpio_number_t _gpio_number{-1};
};

// 複数の Pin を束ねる Port
class Port : public interface::gpio::Port {
public:
    interface::gpio::Pin* getPin(uint8_t pinNumber) override;
};

// GPIO 全体
class GPIO : public interface::gpio::GPIO {
public:
    interface::gpio::Port* getPort(uint8_t portNumber) override;
    interface::gpio::Pin* getPin(m5::hal::types::gpio_number_t pinNumber) override;
};

interface::gpio::GPIO* getGPIO(void);
interface::gpio::Pin* getPin(m5::hal::types::gpio_number_t pinNumber);

}  // namespace gpio
}  // namespace esp32
}  // namespace platforms
}  // namespace hal
}  // namespace m5

#endif  // ESP_PLATFORM && !ARDUINO

#endif
