#include "hal/hal_timer.hpp"
#include "tim.h"

HalTimer::HalTimer() {
    this->ticks = HAL_GetTick();
}

void HalTimer::reset(void) {
    this->ticks = HAL_GetTick();
}

float HalTimer::get_time(void) {
    return (HAL_GetTick() - this->ticks) / 1000.0F;
}
