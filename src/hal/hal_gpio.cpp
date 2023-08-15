#include "hal/hal_gpio.hpp"

HalGpio::HalGpio(const GpioConfig& gpio_config) {
    rcc_periph_clock_enable(gpio_config.rcc_clock);

    gpio_mode_setup(gpio_config.port, gpio_config.mode, gpio_config.pull_up_down, gpio_config.pin);

    this->pin = gpio_config.pin;
    this->port = gpio_config.port;
}

bool HalGpio::read(void) const {
    return gpio_get(this->port, this->pin);
}

void HalGpio::write(bool pin_state) {
    if (pin_state) {
        gpio_set(this->port, this->pin);
    } else {
        gpio_clear(this->port, this->pin);
    }
}

void HalGpio::toggle(void) {
    gpio_toggle(this->port, this->pin);
}
