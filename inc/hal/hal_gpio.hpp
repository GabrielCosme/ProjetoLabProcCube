#ifndef __HAL_GPIO_HPP__
#define __HAL_GPIO_HPP__

#include <cstdint>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

struct GpioConfig {
    uint32_t         port;
    uint8_t          mode;
    uint8_t          pull_up_down;
    uint16_t         pin;
    rcc_periph_clken rcc_clock;
};

class HalGpio {
    public:
        /**
         * @brief Construct a new Hal GPIO object
         *
         * @param gpio_config configuration of the gpio instance
         */
        HalGpio(const GpioConfig& gpio_config);

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
        uint32_t port;

        /**
         * @brief Number of the GPIO pin
         */
        uint16_t pin;
};

#endif // __HAL_GPIO_HPP__
