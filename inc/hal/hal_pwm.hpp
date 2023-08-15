#ifndef __HAL_PWM_HPP__
#define __HAL_PWM_HPP__

#include "tim.h"

// Descomentar depois
// #define TIM_CHANNEL_1 0x00000000U
// #define TIM_CHANNEL_2 0x00000004U

/*****************************************
 * Class Declaration
 *****************************************/

class HalPwm {
    public:
        /**
         * @brief Construct a new Hal Pwm object
         *
         * @param timer_handle Timer handle
         * @param channel Timer channel
         */
        HalPwm(TIM_HandleTypeDef* timer_handle, uint32_t channel);

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
        TIM_HandleTypeDef* timer_handle;
        uint32_t channel;
};

#endif // __HAL_PWM_HPP__
