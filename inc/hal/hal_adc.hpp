#ifndef __HAL_ADC_HPP__
#define __HAL_ADC_HPP__

#include <cstdint>
#include <array>

#include "adc.h"

/*****************************************
 * Class Declaration
 *****************************************/

template <uint8_t number_of_channels, uint16_t reading_per_channel>
class HalAdc {
    public:
        /**
         * @brief Construct a new Hal Adc object
         *
         * @param adc_handle pointer to the ADC handle
         */
        HalAdc(ADC_HandleTypeDef* adc_handle);

        /**
         * @brief Update the ADC reading
         */
        void update_reading(void);

        /**
         * @brief Get the reading of the ADC
         *
         * @param channel channel of the ADC
         * @return uint32_t reading of the ADC channel
         */
        uint32_t get_adc_reading(uint8_t channel) const;

        /**
         * @brief Set the reading done object
         */
        static void set_reading_done(void);

    private:
        ADC_HandleTypeDef* adc_handle;
        uint32_t buffer[number_of_channels * reading_per_channel];
        uint32_t buffer_size = number_of_channels * reading_per_channel;
        static bool reading_done;

        std::array<uint32_t, number_of_channels> adc_reading;
};

#include "../src/hal/hal_adc.cpp"

#endif // __HAL_ADC_HPP__
