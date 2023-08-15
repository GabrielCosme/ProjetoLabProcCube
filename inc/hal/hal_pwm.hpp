#ifndef __HAL_PWM_HPP__
#define __HAL_PWM_HPP__

#include <libopencm3/stm32/timer.h>

struct PwmConfig {
};

class HalPwm {
    public:
        /**
         * @brief Construct a new Hal Pwm object
         *
         * @param pwm_config configuration for the pwm instance
         */
        HalPwm(const PwmConfig& pwm_config);

        /**
         * @brief Start the PWM
         */
        void start(void);

        /**
         * @brief Set the PWM duty cycle
         *
         * @param compare value to set the duty cycle
         */
        void set_compare(uint32_t compare);

    private:
        /**
         * @brief Timer channel
         */
        uint32_t channel;
};

#endif // __HAL_PWM_HPP__
