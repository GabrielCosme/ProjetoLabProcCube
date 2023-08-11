#ifndef __LOCOMOTION_HPP__
#define __LOCOMOTION_HPP__

#include <cstdint>

#include "proxy/motor.hpp"

class Locomotion {
    public:
        Locomotion();

        ~Locomotion() = default;

        void set_speeds(int8_t linear, int8_t angular);

    private:
        Motor left_motor;
        Motor right_motor;
};

#endif // __LOCOMOTION_HPP__
