#include "hal/hal_pwm.hpp"

HalPwm::HalPwm(TIM_HandleTypeDef* timer_handle, uint32_t channel) {
    this->timer_handle = timer_handle;
    this->channel = channel;
}

void HalPwm::start(void) {
    HAL_TIM_PWM_Start(this->timer_handle, this->channel);
}

void HalPwm::set_compare(uint32_t compare) {
    __HAL_TIM_SET_COMPARE(this->timer_handle, this->channel, compare);
}
