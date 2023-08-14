#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include <cstdint>

constexpr float left_deadzone = 0.05;
constexpr float right_deadzone = 0.05;
constexpr float max_stopped_command = 0.02;

constexpr float kp = 1.0;
constexpr float ki = 0.0;
constexpr float kd = 0.0;
constexpr float saturation = 0.0;
constexpr float max_integral = 0.0;

constexpr float filter_frequency = 0.5;

constexpr uint16_t linear_base_speed = 50;
constexpr float linear_decay = 1.0;

#endif // __CONSTANTS_HPP__
