#ifndef __MOTOR_HPP__
#define __MOTOR_HPP__

#include <cstdint>

#include "hal/hal_pwm.hpp"

class Motor {
    public:
        Motor(TIM_HandleTypeDef* htim, float deadzone);

        ~Motor() = default;

        void set_speed(uint8_t speed);

    private:
        Hal_Pwm forward_pwm;
        Hal_Pwm backward_pwm;

        float deadzone;
};

#endif // __MOTOR_HPP__
