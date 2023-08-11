#ifndef __HAL_TIM_HPP__
#define __HAL_TIM_HPP__

#include <cstdint>

/*****************************************
 * Class Declaration
 *****************************************/

class HalTimer {
    public:
        /**
         * @brief Construct a new Hal Timer object
         */
        HalTimer();

        /**
         * @brief Reset the timer
         */
        void reset(void);

        /**
         * @brief Get elapsed time since last reset
         *
         * @return uint32_t elapsed time in milliseconds
         */
        uint32_t get_time(void);

    private:
        /**
         * @brief Ticks since microcontroller startup
         */
        uint32_t ticks;
};

#endif // __HAL_TIM_HPP__
