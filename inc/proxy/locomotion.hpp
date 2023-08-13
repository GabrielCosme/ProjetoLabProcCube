#ifndef __LOCOMOTION_HPP__
#define __LOCOMOTION_HPP__

#include <cstdint>

#include "proxy/motor.hpp"

class Locomotion {
    public:
        /**
         * @brief Construct a new Locomotion object
         */
        Locomotion();

        /**
         * @brief Set the speeds of the motors
         *
         * @param linear Linear speed
         * @param angular Angular speed
         */
        void set_speeds(int8_t linear, int8_t angular);

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

        /**
         * @brief Saturate the command to the motors
         *
         * @param saturated_command command to check if saturated
         * @param other_command command to saturate
         */
        static void saturate_command(int16_t& saturated_command, int16_t& other_command);
};

#endif // __LOCOMOTION_HPP__
