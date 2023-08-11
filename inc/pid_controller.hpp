#ifndef __PID_CONTROLLER_HPP__
#define __PID_CONTROLLER_HPP__

#include "thundervolt_nav/controllers/basics/butterworth_sec_order.h"

namespace thundervolt_nav {
/**
 * @brief Implementation of simple PID controller
 *        Response = Kp(error + Ki * integral(error) Kd * d/dt(error))
 */
class PidController {
    public:
        /**
         * @brief Construct a new Pid Controller object
         *
         * @param kp Proportinal constant
         * @param ki Integrative constant
         * @param kd Derivative constant
         * @param setpoint Desired state
         * @param freq PID sampling frequency
         * @param saturation Maximum response returned by the controller
         * @param max_integral Maximum integrative response
         */
        PidController(double kp, double ki, double kd, double setpoint = 0.0, double saturation = -1.0,
                      double max_integral = -1.0, double integral_fade_rate = 1.0);

        /**
         * @brief Set the setpoint object
         *
         * @param setpoint Desired state
         */
        void set_setpoint(double setpoint);

        /**
         * @brief Set the controller parameters
         *
         * @param kp Proportinal constant
         * @param ki Integrative constant
         * @param kd Derivative constant
         * @param saturation Maximum response returned by the controller
         * @param max_integral Maximum integrative response
         * @param integral_fade_rate Rate at which the accumulated response dissipates
         */
        void set_parameters(double kp, double ki, double kd, double saturation = -1.0, double max_integral = -1.0,
                            double integral_fade_rate = 1.0);

        /**
         * @brief Reset prev_error and error_acc objects
         */
        void reset();

        /**
         * @brief Update PID with new state and return response
         *
         * @param state Current value of the controlled variable
         *
         * @return Response
         */
        double update(double state);

        /**
         * @brief Update PID with new state and return response
         *
         * @param state Current value of the controlled variable
         * @param state_change Derivative of the controlled variable
         *
         * @return Response
         */
        double update(double state, double state_change);

        /**
         * @brief Output stream operator overloading
         */
        friend std::ostream& operator <<(std::ostream& output, const PidController& pid_controller);

    private:
        double kp;           /**< Proportional constant */
        double ki;           /**< Integrative constant */
        double kd;           /**< Derivative constant */
        double setpoint;     /**< Desired state */
        double saturation;   /**< Maximum response returned by the controller */
        double max_integral; /**< Maximum integrative accumulative response */
        double error_acc;    /**< Accumulated error for i term */
        double prev_error;   /**< Previous error for d term */

        ButterworthSecondOrder dedt_filter;  /**< Derivative filter */
};
}  // namespace thundervolt_nav

#endif // __PID_CONTROLLER_HPP__
