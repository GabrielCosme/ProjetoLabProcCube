#ifndef __TARGET_HPP__
#define __TARGET_HPP__

#include <cstdint>

using button_gpio_port = BUTTON_GPIO_Port;
using button_pin = BUTTON_Pin;

using led_gpio_port = LED_GPIO_Port;
using led_pin = LED_Pin;

using left_motor_timer_handle = htim2;
using right_motor_timer_handle = htim1;

using motor_backward_timer_channel = TIM_CHANNEL_2;
using motor_forward_timer_channel = TIM_CHANNEL_1;

constexpr uint16_t motors_timer_counter_period = 1000;
constexpr int16_t max_motors_speed = 100;
constexpr int16_t min_motors_speed = -max_motors_speed;

using line_sensor_adc_handle = hadc1;
constexpr uint16_t adc_num_channels = 8;
constexpr uint16_t adc_readings_per_channel = 50;

#endif // __TARGET_HPP__
