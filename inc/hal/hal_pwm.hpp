#ifndef __HAL_PWM_H__
#define __HAL_PWM_H__

#include "tim.h"

// Descomentar depois
// #define TIM_CHANNEL_1 0x00000000U
// #define TIM_CHANNEL_2 0x00000004U

void hal_pwm_init(void);

void hal_pwm_start(TIM_HandleTypeDef* htim, uint32_t channel);

void hal_pwm_set_compare(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t compare);

#endif // __HAL_PWM_H__
