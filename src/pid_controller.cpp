#include <cmath>

#include "pid_controller.hpp"

/*****************************************
 * Class Methods Bodies Definitions
 *****************************************/

PidController::PidController(float kp, float ki, float kd, float setpoint, float freq, float saturation,
                             float max_integral) :
    kp{kp}, ki{ki}, kd{kd}, setpoint{setpoint}, freq{freq},
    saturation{saturation}, max_integral{max_integral}, error_acc{0.0}, prev_error{0.0} {
}

void PidController::set_setpoint(float setpoint) {
    this->setpoint = setpoint;
}

void PidController::set_parameters(float kp, float ki, float kd, float saturation, float max_integral) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->saturation = saturation;
    this->max_integral = max_integral;
}

void PidController::reset() {
    this->error_acc = 0;
    this->prev_state = 0;
    this->last_response = 0;
}

float PidController::update(float state) {
    uint32_t loop_time_us = this->timer_us.get_time();

    if (loop_time_us == 0) {
        return this->last_response;
    }

    float state_change = (state - this->prev_state) / US_TO_S(loop_time_us);

    return this->update(state, state_change);
}

float PidController::update(float state, float state_change) {
    uint32_t loop_time_us = this->timer_us.get_time();

    if (loop_time_us == 0) {
        return this->last_response;
    }

    float error = this->setpoint - state;
    this->prev_state = state;

    float response = this->kp * (error + this->ki * this->error_acc + this->kd * state_change);

    if (this->saturation < 0 or std::abs(response) < this->saturation or
        this->error_acc != 0 and std::signbit(this->error_acc) != std::signbit(error)) {
        this->error_acc += error * US_TO_S(loop_time_us);
    }

    if (this->max_integral >= 0 and this->ki > 0) {
        this->error_acc = thundervolt_core::constrain(this->error_acc, -this->max_integral / (this->kp * this->ki),
                                                      this->max_integral / (this->kp * this->ki));
    }

    response = this->kp * (error + this->ki * this->error_acc + this->kd * state_change);

    if (this->saturation >= 0 and std::abs(response) >= this->saturation) {
        response = thundervolt_core::constrain(response, -this->saturation, this->saturation);
    }

    this->last_response = response;
    this->timer_us.reset();

    return response;
}
