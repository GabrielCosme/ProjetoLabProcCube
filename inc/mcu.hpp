#ifndef __MCU_HPP__
#define __MCU_HPP__

#include <cstdint>

/**
 * @brief Initializes MCU and some peripherals.
 */
void mcu_init(void);

extern "C" {
/**
 * @brief Initializes System Clock.
 * @note  Defined by cube.
 */
void SystemClock_Config(void);
}

/**
 * @brief Put the MCU to sleep.
 *
 * @param ms  Sleep time in milliseconds
 */
void mcu_sleep(uint32_t ms);

#endif // __MCU_HPP__
