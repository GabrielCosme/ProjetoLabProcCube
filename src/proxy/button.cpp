
#include "proxy/button.hpp"

/*****************************************
 * Private Constants
 *****************************************/

static constexpr uint16_t debounce_delay_ms = 10;
static constexpr uint16_t long_press_time_ms = 900;
static constexpr uint16_t extra_long_press_time_ms = 3000;

/*****************************************
 * Class Definition
 *****************************************/

Button::Button(GPIO_TypeDef* port, uint16_t pin, bool is_pulldown) :
    port(port), pin(pin), is_pulldown(is_pulldown), hal_gpio(port, pin) {
}

void Button::update_state() {
    bool raw_reading = this->is_pressed();

    if ((this->current_state != raw_reading) && !this->is_debouncing) {
        this->is_debouncing = true;
        this->debounce_timer.reset();
    } else if ((this->debounce_timer.get_time() < debounce_delay_ms) && this->is_debouncing) {
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

bool Button::is_rising_edge() {
    return (this->current_state && !this->previous_state);
}

bool Button::is_falling_edge() {
    return (!this->current_state && this->previous_state);
}

bool Button::is_pressed() {
    return (hal_gpio.read() == this->is_pulldown);
}

button_status_t Button::get_status() {
    this->update_state();

    if (this->is_rising_edge()) {
        this->status_timer.reset();
    } else if (this->is_falling_edge()) {
        if (this->status_timer.get_time() > extra_long_press_time_ms) {
            return BUTTON_EXTRA_LONG_PRESS;
        } else if (this->status_timer.get_time() > long_press_time_ms) {
            return BUTTON_LONG_PRESS;
        } else {
            return BUTTON_SHORT_PRESS;
        }
    }

    return BUTTON_NO_PRESS;
}
