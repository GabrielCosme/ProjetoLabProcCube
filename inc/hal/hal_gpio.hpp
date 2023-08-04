#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"

void hal_gpio_init(void);

bool hal_gpio_read(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);

void hal_gpio_write(GPIO_TypeDef* gpio_port, uint16_t gpio_pin, bool pin_state);

#endif // __HAL_GPIO_H__
