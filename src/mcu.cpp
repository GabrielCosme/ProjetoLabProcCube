#include "mcu.hpp"
#include "stm32f4xx_hal.h"

/*****************************************
 * Public Function Body Definitions
 *****************************************/

void mcu_init(void) {
    HAL_Init();

    SystemClock_Config();
}

void mcu_sleep(uint32_t ms) {
    HAL_Delay(ms);
}
