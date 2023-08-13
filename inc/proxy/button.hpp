#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <cstdint>

#include "hal/hal_gpio.hpp"
#include "hal/hal_timer.hpp"

/*****************************************
 * Public Types
 *****************************************/

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
        /**
         * @brief Construct a new Button object
         *
         * @param port pointer to the GPIO port
         * @param pin number of the GPIO pin
         * @param is_pulldown true if the button is connected to ground, false otherwise
         */
        Button(GPIO_TypeDef* port, uint16_t pin, bool is_pulldown);

        /**
         * @brief Provides the status of the chosen button.
         *
         * @return Status of the button.
         */
        button_status_t get_status();

    private:
        GPIO_TypeDef* port;
        uint16_t pin;
        bool is_pulldown;
        HalTimer debounce_timer;
        HalTimer status_timer;
        bool is_debouncing = false;
        bool previous_state = false;
        bool current_state = false;

        HalGpio hal_gpio;

        /**
         * @brief Reads the button state
         *
         * @return bool true if button is pressed
         */
        bool is_pressed() const;

        /**
         * @brief Updates the state of the button
         */
        void update_state();

        /**
         * @brief Checks if the button was just pressed
         *
         * @return true if the button was just pressed, false otherwise
         */
        bool is_rising_edge() const;

        /**
         * @brief Checks if the button was just released
         *
         * @return true if the button was just released, false otherwise
         */
        bool is_falling_edge() const;
};

#endif // __BUTTON_HPP__
