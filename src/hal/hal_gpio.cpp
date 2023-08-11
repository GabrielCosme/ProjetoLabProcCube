
#include "hal/hal_gpio.hpp"

bool HalGpio::is_gpio_inicialized = false;

HalGpio::HalGpio(GPIO_TypeDef* gpio_port, uint16_t gpio_pin) {
    if (!HalGpio::is_gpio_inicialized) {
        HalGpio::is_gpio_inicialized = true;
        MX_GPIO_Init();
    }

    this->gpio_pin = gpio_pin;
    this->gpio_port = gpio_port;
    this->pin_state = GPIO_PIN_RESET;
}

bool HalGpio::read(void) {
    return HAL_GPIO_ReadPin(this->gpio_port, this->gpio_pin);
}

void HalGpio::write(GPIO_PinState pin_state) {
    HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, pin_state);
}
