#ifndef __HAL_TIM_HPP__
#define __HAL_TIM_HPP__

#include <cstdint>

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
         * @return Elapsed time in seconds
         */
        float get_time(void) const;

        /**
         * @brief Sleep for a given amount of time
         *
         * @param milliseconds Time to sleep in milliseconds
         */
        static void sleep(uint32_t milliseconds);

        /**
         * @brief Increment the system ticks
         */
        static void increment_system_ticks(void);

    private:
        /**
         * @brief Ticks since last timer reset
         */
        uint32_t ticks;

        /**
         * @brief Ticks since system start
         */
        static uint32_t system_ticks;
};

#endif // __HAL_TIM_HPP__
