#ifndef __TARGET_HPP__
#define __TARGET_HPP__

#include <cstdint>

#include "gpio.h"
#include "tim.h"
#include "adc.h"
#include "proxy/button.hpp"

GPIO_TypeDef* button_gpio_port = GPIOB;
constexpr uint16_t button_pin = GPIO_PIN_10;
const button_pull_resistor_t button_pull_resistor = BUTTON_PULL_UP;

GPIO_TypeDef* led_gpio_port = GPIOB;
constexpr uint16_t led_pin = GPIO_PIN_15;

TIM_HandleTypeDef* left_motor_timer_handle = &htim2;
TIM_HandleTypeDef* right_motor_timer_handle = &htim1;

constexpr uint16_t motor_backward_timer_channel = TIM_CHANNEL_2;
constexpr uint16_t motor_forward_timer_channel = TIM_CHANNEL_1;

ADC_HandleTypeDef* line_sensor_adc_handle = &hadc1;
constexpr uint8_t adc_num_channels = 8;
constexpr uint16_t adc_readings_per_channel = 50;

#endif // __TARGET_HPP__
