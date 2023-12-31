#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include <cstdint>

#include "hal/hal_pwm.hpp"

constexpr int16_t max_motors_speed = 100;
constexpr int16_t min_motors_speed = -max_motors_speed;

class Motor {
    public:
        /**
         * @brief Construct a new Motor object
         *
         * @param htim pointer to the timer handle
         * @param forward_timer_channel channel of the forward pwm
         * @param backward_timer_channel channel of the backward pwm
         * @param deadzone minimum value of the pwm to start the motor
         */
        Motor(TIM_HandleTypeDef* htim, uint32_t forward_timer_channel, uint32_t backward_timer_channel,
              float deadzone = 0);

        /**
         * @brief Set the speed object
         *
         * @param speed speed of the motor
         */
        void set_speed(int16_t speed);

    private:
        /**
         * @brief pwm to control the motor in forward direction
         */
        HalPwm forward_pwm;

        /**
         * @brief pwm to control the motor in backward direction
         */
        HalPwm backward_pwm;

        /**
         * @brief minimum value of the pwm to start the motor
         */
        float deadzone;
};

#endif // __MOTOR_HPP__
