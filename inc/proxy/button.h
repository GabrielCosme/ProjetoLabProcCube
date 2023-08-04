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
typedef enum button_state {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
} button_state_t;

/**
 * @brief Button pull resistor type
 */
typedef enum button_resistor {
    BUTTON_PULL_UP,
    BUTTON_PULL_DOWN,
} button_resistor_t;

/**
 * @brief Button handler structure.
 */
typedef struct button {
    GPIO_TypeDef*     port;
    uint16_t          pin;
    button_resistor_t pull_resistor;
    uint32_t          debounce_timer;
    bool              is_debouncing;
    button_state_t    previous_state;
    button_state_t    current_state;
} button_t;

/**
 * @brief Button adapter status type
 */
typedef enum button_adapter_status {
    BUTTON_ADAPTER_NO_PRESS,
    BUTTON_ADAPTER_SHORT_PRESS,
    BUTTON_ADAPTER_LONG_PRESS,
    BUTTON_ADAPTER_EXTRA_LONG_PRESS,
} button_adapter_status_t;

/*****************************************
 * Public Functions Prototypes
 *****************************************/

/**
 * @brief Initializes the button
 *
 * @param p_button Pointer to button handler to be Initialized.
 */
void button_init(button_t* p_button, GPIO_TypeDef* port, uint16_t pin, button_resistor_t pull_resistor);

/**
 * @brief Checks if the button was just pressed
 *
 * @param p_button Pointer to button handler
 * @return true if the button was just pressed
 * @return false if the button was not just pressed
 */
bool button_is_rising_edge(button_t* p_button);

/**
 * @brief Checks if the button was just released
 *
 * @param p_button Pointer to button handler
 * @return true if the button was just released
 * @return false if the button was not just released
 */
bool button_is_falling_edge(button_t* p_button);

/**
 * @brief Updates the state of the button
 *
 * @param p_button Pointer to button handler
 */
void button_update_state(button_t* p_button);

/**
 * @brief Reads the button state
 *
 * @param p_button Pointer to button handler
 * @return button_state_t Button state
 */
button_state_t button_reading(button_t* p_button);

/**
 * @brief Provides the status of the chosen button.
 *
 * @return Status of the button.
 */
button_adapter_status_t button_adapter_get_status(void);

#endif // __BUTTON_H__
