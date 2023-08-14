#include <cmath>

#include "proxy/motor.hpp"
#include "hal/hal_pwm.hpp"

Motor::Motor(TIM_HandleTypeDef* htim, float deadzone) :
    forward_pwm(htim, MOTOR_FORWARD_TIMER_CHANNEL), backward_pwm(htim, MOTOR_BACKWARD_TIMER_CHANNEL),
    deadzone(deadzone) {
    forward_pwm.start();
    backward_pwm.start();

    forward_pwm.set_compare(0);
    backward_pwm.set_compare(0);
}

void Motor::set_speed(uint8_t speed) {
    bool command_sign = std::signbit(speed);
    int32_t command = std::abs(constrain(speed, MIN_MOTORS_SPEED, MAX_MOTORS_SPEED));

    if (command <= this->max_stopped_command * MAX_MOTORS_SPEED) {
        command = 0;
    } else {
        command =
            map(command, 0, MAX_PWM_COMMAND, this->deadzone * MOTORS_TIM_COUNTER_PERIOD, MOTORS_TIM_COUNTER_PERIOD);
    }

    if (command_sign) {
        forward_pwm.set_compare(command);
        backward_pwm.set_compare(0);
    } else {
        forward_pwm.set_compare(0);
        backward_pwm.set_compare(command);
    }
}
