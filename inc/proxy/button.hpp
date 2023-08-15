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

enum button_pull_resistor_t {
    BUTTON_PULL_UP,
    BUTTON_PULL_DOWN,
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
         * @param pull_resistor pull resistor configuration
         */
        Button(uint32_t port, uint16_t pin, button_pull_resistor_t pull_resistor);

        /**
         * @brief Provides the status of the chosen button.
         *
         * @return Status of the button.
         */
        button_status_t get_status();

    private:
        /**
         * @brief number of the GPIO port
         */
        uint32_t port;

        /**
         * @brief number of the GPIO pin
         */
        uint16_t pin;

        /**
         * @brief pull resistor configuration
         */
        button_pull_resistor_t pull_resistor;

        /**
         * @brief timer to check if button is debouncing
         */
        HalTimer debounce_timer;

        /**
         * @brief timer to determine type of button press
         */
        HalTimer status_timer;

        /**
         * @brief flag to know when button is debouncing
         */
        bool is_debouncing = false;

        /**
         * @brief flag to know if button was being pressed
         */
        bool previous_state = false;

        /**
         * @brief flag to know if button is being pressed
         */
        bool current_state = false;

        /**
         * @brief gpio where the button is read from
         */
        const HalGpio hal_gpio;

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
