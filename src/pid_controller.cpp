#include <cmath>

#include "thundervolt_core/utils.h"
#include "thundervolt_nav/controllers/basics/pid_controller.h"

/*****************************************
 * Private Constants
 *****************************************/

/**
 * @brief Cutoff frequency is 1/5 of the sampling frequency
 */
static constexpr double cutoff_and_sampling_freqs_relat{0.2};

static const std::string pid_logger_name{"pid_controller"};

/*****************************************
 * Class Methods Bodies Definitions
 *****************************************/

PidController::PidController(double kp, double ki, double kd, double setpoint, double freq, double saturation,
                             double max_integral) :
    kp{kp}, ki{ki}, kd{kd}, setpoint{setpoint}, freq{freq},
    saturation{saturation}, max_integral{max_integral}, error_acc{0.0}, prev_error{0.0},
    dedt_filter{freq * cutoff_and_sampling_freqs_relat, freq} {
}

void PidController::set_setpoint(double setpoint) {
    this->setpoint = setpoint;
}

void PidController::set_parameters(double kp, double ki, double kd, double saturation, double max_integral) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->saturation = saturation;
    this->max_integral = max_integral;
}

void PidController::reset() {
    this->error_acc = 0;
    this->prev_error = 0;
}

double PidController::update(double state) {
    uint32_t loop_time_us = get_timer_us(p_pid->timer_us);

    if (loop_time_us == 0) {
        return p_pid->last_response;
    }

    double error = this->setpoint - state;
    double dedt = this->dedt_filter.update((error - this->prev_error) * this->freq);

    return this->update(error, dedt);
}

double PidController::update(double state, double state_change) {
    uint32_t loop_time_us = get_timer_us(p_pid->timer_us);

    if (loop_time_us == 0) {
        return p_pid->last_response;
    }

    double error = this->setpoint - state;

    this->prev_error = error;

    double response = this->kp * (error + this->ki * this->error_acc + this->kd * state_change);

    if (this->saturation < 0 or std::abs(response) < this->saturation or
        this->error_acc != 0 and std::signbit(this->error_acc) != std::signbit(error)) {
        this->error_acc += error / this->freq;
    }

    if (this->max_integral >= 0 and this->ki > 0) {
        this->error_acc = thundervolt_core::constrain(this->error_acc, -this->max_integral / (this->kp * this->ki),
                                                      this->max_integral / (this->kp * this->ki));
    }

    response = this->kp * (error + this->ki * this->error_acc + this->kd * state_change);

    if (this->saturation >= 0 and std::abs(response) >= this->saturation) {
        response = thundervolt_core::constrain(response, -this->saturation, this->saturation);
    }

    return response;
}
