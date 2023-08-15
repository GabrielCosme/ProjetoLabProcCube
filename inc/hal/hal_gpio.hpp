#ifndef __HAL_GPIO_HPP__
#define __HAL_GPIO_HPP__

#include <cstdint>
#include <libopencm3/stm32/gpio.h>

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
        HalGpio(uint32_t gpio_port, uint8_t gpio_mode, uint8_t pull_up_down, uint16_t gpio_pin);

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
        void write(bool pin_state);

        /**
         * @brief Toggle the GPIO pin
         */
        void toggle(void);

    private:
        /**
         * @brief Pointer to the GPIO port
         */
        uint32_t gpio_port;

        /**
         * @brief Number of the GPIO pin
         */
        uint16_t gpio_pin;
};

#endif // __HAL_GPIO_HPP__
