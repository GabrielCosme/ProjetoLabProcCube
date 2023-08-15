#include <cmath>

#include "proxy/locomotion.hpp"

Locomotion::Locomotion(TIM_HandleTypeDef* left_motor_timer_handle, TIM_HandleTypeDef* right_motor_timer_handle,
                       uint32_t forward_timer_channel, uint32_t backward_timer_channel, float left_deadzone,
                       float right_deadzone) :
    left_motor(left_motor_timer_handle, forward_timer_channel, backward_timer_channel, left_deadzone),
    right_motor(right_motor_timer_handle, forward_timer_channel, backward_timer_channel, right_deadzone) {
}

void Locomotion::set_speeds(int16_t linear, int16_t angular) {
    uint16_t left_command = linear + angular;
    uint16_t right_command = linear - angular;

    if (std::abs(left_command) > max_motors_speed) {
        left_command *= max_motors_speed / std::abs(left_command);
        right_command *= max_motors_speed / std::abs(left_command);
    }

    if (std::abs(right_command) > max_motors_speed) {
        left_command *= max_motors_speed / std::abs(right_command);
        right_command *= max_motors_speed / std::abs(right_command);
    }

    this->left_motor.set_speed(left_command);
    this->right_motor.set_speed(right_command);
}

float Locomotion::linear_decay(float angular_error, float dependency) {
    return dependency / (dependency + angular_error * angular_error);
}
