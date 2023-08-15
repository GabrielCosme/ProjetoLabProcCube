#include "hal/hal_pwm.hpp"

HalPwm::HalPwm(TIM_HandleTypeDef* htim, uint32_t channel) {
    MX_TIM1_Init();
    MX_TIM2_Init();
    this->tim_handle = htim;
    this->channel = channel;
}

void HalPwm::start(void) {
    HAL_TIM_PWM_Start(this->tim_handle, this->channel);
}

void HalPwm::set_compare(uint32_t compare) {
    __HAL_TIM_SET_COMPARE(this->tim_handle, this->channel, compare);
}
