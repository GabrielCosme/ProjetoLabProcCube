#ifndef __HAL_PWM_HPP__
#define __HAL_PWM_HPP__

#include <cstdint>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

#include "hal_gpio.hpp"

struct PwmConfig {
    GpioConfig       gpio;
    rcc_periph_clken rcc_timer_clock;
    uint32_t         timer;
    uint32_t         period;
    tim_oc_id        oc_id;
    tim_oc_mode      oc_mode;
    uint8_t          irqn;
};

class HalPwm {
    public:
        /**
         * @brief Construct a new Hal Pwm object
         *
         * @param pwm_config Configuration for the pwm instance
         */
        HalPwm(const PwmConfig& pwm_config);

        /**
         * @brief Set the PWM duty cycle
         *
         * @param compare Value to set the duty cycle
         */
        void set_compare(uint32_t compare);

    private:
        /**
         * @brief Timer channel
         */
        uint32_t channel;
};

#endif // __HAL_PWM_HPP__
