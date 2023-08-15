#ifndef __HAL_PWM_HPP__
#define __HAL_PWM_HPP__

#include "tim.h"

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
        /**
         * @brief pointer to the timer handle
         */
        TIM_HandleTypeDef* timer_handle;

        /**
         * @brief Timer channel
         */
        uint32_t channel;
};

#endif // __HAL_PWM_HPP__
