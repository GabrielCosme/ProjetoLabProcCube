
#include "proxy/button.hpp"
#include <libopencm3/stm32/gpio.h>

/*****************************************
 * Private Constants
 *****************************************/

static constexpr float debounce_delay = 0.01;
static constexpr float long_press_time = 0.9;
static constexpr float extra_long_press_time = 3.0;

/*****************************************
 * Class Definition
 *****************************************/

Button::Button(uint32_t port, uint16_t pin, button_pull_resistor_t pull_resistor) :
    port(port), pin(pin), pull_resistor(pull_resistor),
    hal_gpio(port, GPIO_MODE_INPUT, pull_resistor == BUTTON_PULL_UP ? GPIO_PUPD_PULLUP : GPIO_PUPD_PULLDOWN, pin) {
}

void Button::update_state() {
    bool raw_reading = this->is_pressed();

    if ((this->current_state != raw_reading) && !this->is_debouncing) {
        this->is_debouncing = true;
        this->debounce_timer.reset();
    } else if ((this->debounce_timer.get_time() < debounce_delay) && this->is_debouncing) {
        if (this->current_state == raw_reading) {
            this->is_debouncing = false;
            return;
        }
    } else {
        this->is_debouncing = false;
        this->previous_state = this->current_state;
        this->current_state = raw_reading;
    }
}

bool Button::is_rising_edge() const {
    return (this->current_state && !this->previous_state);
}

bool Button::is_falling_edge() const {
    return (!this->current_state && this->previous_state);
}

bool Button::is_pressed() const {
    return ((int) this->hal_gpio.read() == (int) this->pull_resistor);
}

button_status_t Button::get_status() {
    this->update_state();

    if (this->is_rising_edge()) {
        this->status_timer.reset();
    } else if (this->is_falling_edge()) {
        if (this->status_timer.get_time() > extra_long_press_time) {
            return BUTTON_EXTRA_LONG_PRESS;
        } else if (this->status_timer.get_time() > long_press_time) {
            return BUTTON_LONG_PRESS;
        } else {
            return BUTTON_SHORT_PRESS;
        }
    }

    return BUTTON_NO_PRESS;
}
