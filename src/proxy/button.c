
#include "proxy/button.h"

/*****************************************
 * Private Constants
 *****************************************/

#define DEBOUNCE_DELAY_MS 10
#define LONG_PRESS_TIME_MS 900
#define EXTRA_LONG_PRESS_TIME_MS 3000

/*****************************************
 * Private Variables
 *****************************************/

static uint32_t m_button_timer;

static button_handler_t m_button;

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void button_handler_init(button_handler_t* p_button, GPIO_TypeDef* port, uint16_t pin,
                         button_handler_resistor_t pull_resistor) {
    p_button->port = port;
    p_button->pin = pin;
    p_button->pull_resistor = pull_resistor;
    p_button->debounce_timer = 0;
    p_button->is_debouncing = false;
    p_button->previous_state = false;
    p_button->current_state = false;
}

button_handler_state_t button_handler_get_current_state(button_handler_t* p_button) {
    return p_button->current_state;
}

button_handler_state_t button_handler_get_previous_state(button_handler_t* p_button) {
    return p_button->previous_state;
}

bool button_handler_is_rising_edge(button_handler_t* p_button) {
    return (p_button->current_state && !p_button->previous_state);
}

bool button_handler_is_falling_edge(button_handler_t* p_button) {
    return (!p_button->current_state && p_button->previous_state);
}

void button_handler_update_state(button_handler_t* p_button) {
    button_handler_state_t raw_reading = button_reading(p_button);

    if ((p_button->current_state != raw_reading) && !p_button->is_debouncing) {
        p_button->is_debouncing = true;
        reset_timer_ms(p_button->debounce_timer);
    } else if ((get_timer_ms(p_button->debounce_timer) < DEBOUNCE_DELAY_MS) && p_button->is_debouncing) {
        if (p_button->current_state == raw_reading) {
            p_button->is_debouncing = false;
            return;
        }
    } else {
        p_button->is_debouncing = false;
        p_button->previous_state = p_button->current_state;
        p_button->current_state = raw_reading;
    }
}

button_handler_state_t button_reading(button_handler_t* p_button) {
    return ((int) HAL_GPIO_ReadPin(p_button->port, p_button->pin) == (int) p_button->pull_resistor);
}

void button_adapter_init(void) {
    MX_GPIO_Init();

    button_handler_init(&m_button, TARGET_BUTTON_ONE_PORT, TARGET_BUTTON_ONE_PIN, BUTTON_HANDLER_PULL_UP);
}

button_adapter_status_t button_adapter_get_status(void) {
    button_handler_update_state(&m_button);

    if (button_handler_is_rising_edge(&m_button)) {
        reset_timer_ms(m_button_timer);
    } else if (button_handler_is_falling_edge(&m_button)) {
        if (get_timer_ms(m_button_timer) > EXTRA_LONG_PRESS_TIME_MS) {
            return BUTTON_ADAPTER_EXTRA_LONG_PRESS;
        } else if (get_timer_ms(m_button_timer) > LONG_PRESS_TIME_MS) {
            return BUTTON_ADAPTER_LONG_PRESS;
        } else {
            return BUTTON_ADAPTER_SHORT_PRESS;
        }
    }

    return BUTTON_ADAPTER_NO_PRESS;
}
