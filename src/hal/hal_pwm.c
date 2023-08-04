#include "hal/hal_pwm.h"

void hal_pwm_init(void) {
    MX_TIM1_Init();
    MX_TIM2_Init();
}

void hal_pwm_start(TIM_HandleTypeDef* htim, uint32_t channel) {
    HAL_TIM_PWM_Start(htim, channel);
}

void hal_pwm_set_compare(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t compare) {
    __HAL_TIM_SET_COMPARE(htim, channel, compare);
}
