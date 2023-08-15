#ifndef __TARGET_HPP__
#define __TARGET_HPP__

#include <cstdint>

#include "adc.h"
#include "tim.h"

#include <libopencm3/stm32/gpio.h>

#include "proxy/button.hpp"

uint32_t button_gpio_port = GPIOB;
constexpr uint16_t button_pin = GPIO10;
const button_pull_resistor_t button_pull_resistor = BUTTON_PULL_UP;

uint32_t led_gpio_port = GPIOB;
constexpr uint16_t led_pin = GPIO15;
uint8_t led_gpio_mode = GPIO_MODE_OUTPUT;

TIM_HandleTypeDef* left_motor_timer_handle = &htim2;
TIM_HandleTypeDef* right_motor_timer_handle = &htim1;

constexpr uint16_t motor_forward_timer_channel = TIM_CHANNEL_1;
constexpr uint16_t motor_backward_timer_channel = TIM_CHANNEL_2;

ADC_HandleTypeDef* line_sensor_adc_handle = &hadc1;
constexpr uint8_t adc_num_channels = 8;
constexpr uint16_t adc_readings_per_channel = 50;

#endif // __TARGET_HPP__
