
#include "proxy/buttons.hpp"

/*****************************************
 * Private Constants
 *****************************************/

static constexpr uint16_t debounce_delay_ms 10
static constexpr uint16_t long_press_time_ms 900
static constexpr uint16_t extra_long_press_time_ms 3000

/*****************************************
 * Class Definition
 *****************************************/

Button::Button(GPIO_TypeDef* port, uint16_t pin, button_resistor_t pull_resistor) :
    port(port), pin(pin), pull_resistor(pull_resistor) {
    hal_gpio_init();

    debounce_timer = 0;
}

void Button::update_state() {
    button_state_t raw_reading = this->get_reading();

    if ((this->current_state != raw_reading) && !this->is_debouncing) {
        this->is_debouncing = true;
        reset_timer_ms(this->debounce_timer);
    } else if ((get_timer_ms(this->debounce_timer) < DEBOUNCE_DELAY_MS) && this->is_debouncing) {
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

button_state_t Button::get_reading() {
    return (hal_gpio_read(this->port, this->pin) == this->pull_resistor);
}

button_status_t Button::get_status() {
    this->update_state();

    if (this->is_rising_edge()) {
        reset_timer_ms(this->status_timer);
    } else if (this->is_falling_edge()) {
        if (get_timer_ms(this->status_timer) > EXTRA_LONG_PRESS_TIME_MS) {
            return BUTTON_EXTRA_LONG_PRESS;
        } else if (get_timer_ms(this->status_timer) > LONG_PRESS_TIME_MS) {
            return BUTTON_LONG_PRESS;
        } else {
            return BUTTON_SHORT_PRESS;
        }
    }

    return BUTTON_NO_PRESS;
}
