#ifndef __LOCOMOTION_HPP__
#define __LOCOMOTION_HPP__

#include <cstdint>

#include "proxy/motor.hpp"

class Locomotion {
    public:
        /**
         * @brief Construct a new Locomotion object
         *
         * @param left_motor_timer_handle pointer to the left motor timer handle
         * @param right_motor_timer_handle pointer to the right motor timer handle
         * @param forward_timer_channel channel of the forward pwm
         * @param backward_timer_channel channel of the backward pwm
         * @param left_deadzone deadzone of the left motor
         * @param right_deadzone deadzone of the right motor
         */
        Locomotion(TIM_HandleTypeDef* left_motor_timer_handle, TIM_HandleTypeDef* right_motor_timer_handle,
                   uint32_t forward_timer_channel, uint32_t backward_timer_channel, float left_deadzone = 0,
                   float right_deadzone = 0);

        /**
         * @brief Set the speeds of the motors
         *
         * @param linear Linear speed
         * @param angular Angular speed
         */
        void set_speeds(int16_t linear, int16_t angular);

        /**
         * @brief Compute the linear decay of the angular error
         *
         * @param angular_error Angular error
         * @param dependency Dependency of the linear decay
         * @return float Linear decay
         */
        static float linear_decay(float angular_error, float dependency);

    private:
        Motor left_motor;
        Motor right_motor;
};

#endif // __LOCOMOTION_HPP__
