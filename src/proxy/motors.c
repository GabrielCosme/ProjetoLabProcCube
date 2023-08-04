#include "proxy/motors.h"
#include "hal/hal_pwm.h"

#define MOTOR_LEFT_TIM_HANDLE (htim2)
#define MOTOR_RIGHT_TIM_HANDLE (htim1)

#define MOTORS_TIM_COUNTER_PERIOD 1000

#define MOTOR_LEFT_BACKWARD_TIM_CH TIM_CHANNEL_2
#define MOTOR_LEFT_FORWARD_TIM_CH TIM_CHANNEL_1
#define MOTOR_RIGHT_BACKWARD_TIM_CH TIM_CHANNEL_2
#define MOTOR_RIGHT_FORWARD_TIM_CH TIM_CHANNEL_1

void motors_init(void) {
    hal_pwm_init();

    hal_pwm_start(&MOTOR_RIGHT_TIM_HANDLE, TIM_CHANNEL_1);
    hal_pwm_start(&MOTOR_RIGHT_TIM_HANDLE, TIM_CHANNEL_2);
    hal_pwm_start(&MOTOR_LEFT_TIM_HANDLE, TIM_CHANNEL_1);
    hal_pwm_start(&MOTOR_LEFT_TIM_HANDLE, TIM_CHANNEL_2);

    hal_pwm_set_compare(&MOTOR_RIGHT_TIM_HANDLE, TIM_CHANNEL_1, 0);
    hal_pwm_set_compare(&MOTOR_RIGHT_TIM_HANDLE, TIM_CHANNEL_2, 0);
    hal_pwm_set_compare(&MOTOR_LEFT_TIM_HANDLE, TIM_CHANNEL_1, 0);
    hal_pwm_set_compare(&MOTOR_LEFT_TIM_HANDLE, TIM_CHANNEL_2, 0);
}

void motors_set_speed(uint8_t left_speed, uint8_t right_speed) {
    int32_t command_left = abs(constrain(left_speed, MOTORS_MIN_COMMAND, MOTORS_MAX_COMMAND));
    int32_t command_right = abs(constrain(right_speed, MOTORS_MIN_COMMAND, MOTORS_MAX_COMMAND));

    command_left = map(command_left, 0, MOTORS_MAX_COMMAND, 0, MOTORS_TIM_COUNTER_PERIOD);
    command_right = map(command_right, 0, MOTORS_MAX_COMMAND, 0, MOTORS_TIM_COUNTER_PERIOD);

    if (left_speed > 0) {
        hal_pwm_set_compare(&MOTOR_LEFT_TIM_HANDLE, MOTOR_LEFT_FORWARD_TIM_CH, command_left);
        hal_pwm_set_compare(&MOTOR_LEFT_TIM_HANDLE, MOTOR_LEFT_BACKWARD_TIM_CH, 0);
    } else {
        hal_pwm_set_compare(&MOTOR_LEFT_TIM_HANDLE, MOTOR_LEFT_FORWARD_TIM_CH, 0);
        hal_pwm_set_compare(&MOTOR_LEFT_TIM_HANDLE, MOTOR_LEFT_BACKWARD_TIM_CH, command_left);
    }

    if (right_speed > 0) {
        hal_pwm_set_compare(&MOTOR_RIGHT_TIM_HANDLE, MOTOR_RIGHT_FORWARD_TIM_CH, command_right);
        hal_pwm_set_compare(&MOTOR_RIGHT_TIM_HANDLE, MOTOR_RIGHT_BACKWARD_TIM_CH, 0);
    } else {
        hal_pwm_set_compare(&MOTOR_RIGHT_TIM_HANDLE, MOTOR_RIGHT_FORWARD_TIM_CH, 0);
        hal_pwm_set_compare(&MOTOR_RIGHT_TIM_HANDLE, MOTOR_RIGHT_BACKWARD_TIM_CH, command_right);
    }
}
