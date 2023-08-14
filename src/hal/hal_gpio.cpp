#include "hal/hal_gpio.hpp"

HalGpio::HalGpio(GPIO_TypeDef* gpio_port, uint16_t gpio_pin) {
    MX_GPIO_Init();

    this->gpio_pin = gpio_pin;
    this->gpio_port = gpio_port;
}

bool HalGpio::read(void) const {
    return HAL_GPIO_ReadPin(this->gpio_port, this->gpio_pin);
}

void HalGpio::write(GPIO_PinState pin_state) {
    HAL_GPIO_WritePin(this->gpio_port, this->gpio_pin, pin_state);
}

void HalGpio::toggle(void) {
    HAL_GPIO_TogglePin(this->gpio_port, this->gpio_pin);
}
