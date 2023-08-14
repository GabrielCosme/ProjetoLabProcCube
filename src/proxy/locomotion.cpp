#include "proxy/locomotion.hpp"

Locomotion::Locomotion() :
    left_motor(left_motor_timer_handle, left_deadzone), right_motor(right_motor_timer_handle, right_deadzone) {
}

void Locomotion::set_speeds(int16_t linear, int16_t angular) {
    uint32_t left_command = linear + angular;
    uint32_t right_command = linear - angular;

    saturate_command(left_command, right_command);
    saturate_command(right_command, left_command);

    this->left_motor.set_speed(left_command);
    this->left_motor.set_speed(right_command);
}

static float Locomotion::linear_decay(float angular_error, float dependency) {
    return dependency / (dependency + angular_error * angular_error);
}

static void Locomotion::saturate_command(int16_t& saturated_command, int16_t& other_command) {
    if (saturated_command > MAX_MOTORS_SPEED) {
        other_command *= MAX_MOTORS_SPEED / saturated_command;
        saturated_command = MAX_MOTORS_SPEED;
    }

    if (saturated_command < MIN_MOTORS_SPEED) {
        other_command *= MIN_MOTORS_SPEED / saturated_command;
        saturated_command = MIN_MOTORS_SPEED;
    }
}
