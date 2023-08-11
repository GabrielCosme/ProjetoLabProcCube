#include "hal/hal_timer.hpp"
#include "tim.h"

HalTimer::HalTimer() {
    this->ticks = HAL_GetTick();
}

void HalTimer::reset(void) {
    this->ticks = HAL_GetTick();
}

uint32_t HalTimer::get_time(void) {
    return HAL_GetTick() - this->ticks;
}
