#ifndef M5_HAL_PLATFORMS_ESPRESSIF_GPIO_INL
#define M5_HAL_PLATFORMS_ESPRESSIF_GPIO_INL

#include "./gpio.hpp"

#if defined(ESP_PLATFORM) && !defined(ARDUINO)

#include <driver/gpio.h>

#include <vector>
#include <list>

namespace m5 {
namespace hal {
namespace platforms {
namespace esp32 {
namespace gpio {

interface::gpio::GPIO* getGPIO(void)
{
    static GPIO s_gpio_instance;
    return &s_gpio_instance;
}

interface::gpio::Pin* getPin(m5::hal::types::gpio_number_t pinNumber)
{
    return getGPIO()->getPin(pinNumber);
}

interface::gpio::Port* GPIO::getPort(uint8_t portNumber)
{
    static Port s_port_instance;
    return &s_port_instance;
}

interface::gpio::Pin* GPIO::getPin(m5::hal::types::gpio_number_t pinNumber)
{
    return getPort(0)->getPin(pinNumber);
}

interface::gpio::Pin* Port::getPin(uint8_t pinNumber)
{
    static std::vector<Pin*> s_pins_pointer;
    static std::list<Pin> s_pins_instance;
    if (s_pins_pointer.size() <= pinNumber) {
        s_pins_pointer.resize(pinNumber + 1, nullptr);
    }
    if (s_pins_pointer[pinNumber] == nullptr) {
        s_pins_instance.push_back(Pin(pinNumber));
        s_pins_pointer[pinNumber] = &s_pins_instance.back();
    }
    return s_pins_pointer[pinNumber];
}

void Pin::write(bool value)
{
    gpio_set_level(static_cast<gpio_num_t>(_gpio_number), value ? 1 : 0);
}

bool Pin::read(void)
{
    return gpio_get_level(static_cast<gpio_num_t>(_gpio_number)) != 0;
}

void Pin::writeHigh(void)
{
    gpio_set_level(static_cast<gpio_num_t>(_gpio_number), 1);
}

void Pin::writeLow(void)
{
    gpio_set_level(static_cast<gpio_num_t>(_gpio_number), 0);
}

void Pin::setMode(m5::hal::types::gpio_mode_t mode)
{
    const gpio_num_t num = static_cast<gpio_num_t>(_gpio_number);
    switch (mode) {
        case m5::hal::types::gpio_mode_t::Input:
            gpio_set_direction(num, GPIO_MODE_INPUT);
            break;
        case m5::hal::types::gpio_mode_t::Output:
            gpio_set_direction(num, GPIO_MODE_OUTPUT);
            break;
        case m5::hal::types::gpio_mode_t::Output_OpenDrain:
            // OD でも線を読めるよう INPUT_OUTPUT_OD にする (clock stretch / ACK 検出)
            gpio_set_direction(num, GPIO_MODE_INPUT_OUTPUT_OD);
            break;
        default:
            break;
    }
}

}  // namespace gpio
}  // namespace esp32
}  // namespace platforms
}  // namespace hal
}  // namespace m5

#endif  // ESP_PLATFORM && !ARDUINO

#endif
