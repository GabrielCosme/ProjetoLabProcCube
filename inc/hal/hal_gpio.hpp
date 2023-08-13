#ifndef __HAL_GPIO_HPP__
#define __HAL_GPIO_HPP__

#include <cstdint>

#include "gpio.h"

/*****************************************
 * Class Declaration
 *****************************************/

class HalGpio {
    public:
        /**
         * @brief Construct a new Hal GPIO object
         *
         * @param gpio_port pointer to the GPIO port
         * @param gpio_pin number of the GPIO pin
         */
        HalGpio(GPIO_TypeDef* gpio_port, uint16_t gpio_pin);

        /**
         * @brief Read the GPIO pin
         *
         * @return true if the pin is high, false otherwise
         */
        bool read(void) const;

        /**
         * @brief Write to the GPIO pin
         *
         * @param pin_state state of the GPIO pin
         */
        void write(GPIO_PinState pin_state) const;

    private:
        /**
         * @brief Pointer to the GPIO port
         */
        GPIO_TypeDef* gpio_port;

        /**
         * @brief Number of the GPIO pin
         */
        uint16_t gpio_pin;
};

#endif // __HAL_GPIO_HPP__
