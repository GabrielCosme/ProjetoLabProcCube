#include <cmath>

#include "proxy/motor.hpp"
#include "hal/hal_pwm.hpp"
#include "utils.hpp"

static constexpr uint16_t motors_timer_counter_period = 1000;
static constexpr float max_stopped_command = 0.02;

Motor::Motor(TIM_HandleTypeDef* htim, uint32_t forward_timer_channel, uint32_t backward_timer_channel, float deadzone) :
    forward_pwm(htim, forward_timer_channel), backward_pwm(htim, backward_timer_channel),
    deadzone(deadzone) {
    forward_pwm.start();
    backward_pwm.start();

    forward_pwm.set_compare(0);
    backward_pwm.set_compare(0);
}

void Motor::set_speed(uint8_t speed) {
    bool command_sign = std::signbit(speed);
    int32_t command = std::abs(constrain(speed, min_motors_speed, max_motors_speed));

    if (command <= max_stopped_command * max_motors_speed) {
        command = 0;
    } else {
        command = map(command, 0, max_motors_speed,
                      this->deadzone * motors_timer_counter_period, motors_timer_counter_period);
    }

    if (command_sign) {
        forward_pwm.set_compare(command);
        backward_pwm.set_compare(0);
    } else {
        forward_pwm.set_compare(0);
        backward_pwm.set_compare(command);
    }
}
