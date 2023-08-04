#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <stdbool.h>
#include <stdint.h>

#include "hal/hal_gpio.h"

/*****************************************
 * Public Types
 *****************************************/

/**
 * @brief Button state type
 */
enum button_state_t {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
};

/**
 * @brief Button pull resistor type
 */
enum button_resistor_t {
    BUTTON_PULL_UP,
    BUTTON_PULL_DOWN,
};

/**
 * @brief Button status type
 */
enum button_status_t {
    BUTTON_NO_PRESS,
    BUTTON_SHORT_PRESS,
    BUTTON_LONG_PRESS,
    BUTTON_EXTRA_LONG_PRESS,
};

/*****************************************
 * Class Declaration
 *****************************************/

class Button {
    public:
        Button(GPIO_TypeDef* port, uint16_t pin, button_resistor_t pull_resistor);

        ~Button() = default;

        /**
         * @brief Reads the button state
         *
         * @return button_state_t Button state
         */
        button_state_t get_reading() const;

        /**
         * @brief Provides the status of the chosen button.
         *
         * @return Status of the button.
         */
        button_status_t get_status();

    private:
        GPIO_TypeDef* port;
        uint16_t pin;
        button_resistor_t pull_resistor;
        uint32_t debounce_timer = 0;
        uint32_t status_timer = 0;
        bool is_debouncing = false;
        button_state_t previous_state = BUTTON_RELEASED;
        button_state_t current_state = BUTTON_RELEASED;

        /**
         * @brief Updates the state of the button
         */
        update_state();

        /**
         * @brief Checks if the button was just pressed
         *
         * @return true if the button was just pressed, false otherwise
         */
        is_rising_edge() const;

        /**
         * @brief Checks if the button was just released
         *
         * @return true if the button was just released, false otherwise
         */
        is_falling_edge() const;
};

#endif // __BUTTON_H__
