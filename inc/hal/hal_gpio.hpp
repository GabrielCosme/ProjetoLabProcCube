#ifndef __HAL_GPIO_HPP__
#define __HAL_GPIO_HPP__

#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"

/*****************************************
 * Class Declaration
 *****************************************/

class HalGpio {
    public:
        HalGpio(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);

        bool read(void);

        void write(GPIO_PinState pin_state);

    private:
        GPIO_TypeDef* gpio_port;
        uint16_t gpio_pin;
        GPIO_PinState pin_state;
        static bool is_gpio_inicialized;
};

#endif // __HAL_GPIO_HPP__
