
#include "hal/hal_gpio.h"

void hal_gpio_init(void) {
    MX_GPIO_Init();
}

bool hal_gpio_read(GPIO_TypeDef* gpio_port, uint16_t gpio_pin) {
    return HAL_GPIO_ReadPin(gpio_port, gpio_pin);
}

void hal_gpio_write(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, bool pin_state) {
    HAL_GPIO_WritePin(gpio_port, gpio_pin, pin_state);
}
