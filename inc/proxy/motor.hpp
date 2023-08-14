#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include <cstdint>

#include "hal/hal_pwm.hpp"

class Motor {
    public:
        /**
         * @brief Construct a new Motor object
         *
         * @param htim pointer to the timer handler
         * @param deadzone minumum command to start the motor
         */
        Motor(TIM_HandleTypeDef* htim, float deadzone);

        /**
         * @brief Set the speed object
         *
         * @param speed speed of the motor
         */
        void set_speed(uint8_t speed);

    private:
        HalPwm forward_pwm;
        HalPwm backward_pwm;

        float deadzone;
};

#endif // __MOTOR_HPP__
