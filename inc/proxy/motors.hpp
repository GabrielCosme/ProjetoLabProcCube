#ifndef __MOTORS_H__
#define __MOTORS_H__

#include <stdint.h>

#define MOTORS_MAX_COMMAND 100
#define MOTORS_MIN_COMMAND -100

void motors_init(void);

void motors_set_speed(uint8_t left_speed, uint8_t right_speed);

#endif // __MOTORS_H__
