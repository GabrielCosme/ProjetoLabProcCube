#include "hal/hal_gpio.hpp"
#include <libopencm3/stm32/rcc.h>

HalGpio::HalGpio(uint32_t gpio_port, uint8_t gpio_mode, uint8_t pull_up_down, uint16_t gpio_pin) {
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_mode_setup(gpio_port, gpio_mode, pull_up_down, gpio_pin);

    this->gpio_pin = gpio_pin;
    this->gpio_port = gpio_port;
}

bool HalGpio::read(void) const {
    return gpio_get(this->gpio_port, this->gpio_pin);
}

void HalGpio::write(bool pin_state) {
    if (pin_state) {
        gpio_set(this->gpio_port, this->gpio_pin);
    } else {
        gpio_clear(this->gpio_port, this->gpio_pin);
    }
}

void HalGpio::toggle(void) {
    gpio_toggle(this->gpio_port, this->gpio_pin);
}
