#ifndef __HAL_ADC_HPP__
#define __HAL_ADC_HPP__

#include <cstdint>
#include <array>

#include "adc.h"

struct AdcConfig {
};

template <uint8_t number_of_channels, uint16_t reading_per_channel>
class HalAdc {
    public:
        /**
         * @brief Construct a new Hal Adc object
         *
         * @param adc_config Configuration of the ADC
         */
        HalAdc(const AdcConfig& adc_config);

        /**
         * @brief Update the ADC reading
         */
        void update_reading(void);

        /**
         * @brief Get the reading of the ADC
         *
         * @param channel Channel of the ADC
         * @return uint32_t Reading of the ADC channel
         */
        uint32_t get_adc_reading(uint8_t channel) const;

        /**
         * @brief Set the reading done object
         */
        static void set_reading_done(void);

    private:
        /**
         * @brief Pointer to the ADC handle
         */
        ADC_HandleTypeDef* adc_handle;

        /**
         * @brief Buffer to store the ADC reading
         */
        uint32_t buffer[number_of_channels * reading_per_channel];

        /**
         * @brief Size of the buffer
         */
        uint32_t buffer_size = number_of_channels * reading_per_channel;

        /**
         * @brief Static flag to indicate if the reading is done
         */
        static bool reading_done;

        /**
         * @brief Array to store the average ADC reading of each channel
         */
        std::array<uint32_t, number_of_channels> adc_reading;
};

#include "../src/hal/hal_adc.cpp"

#endif // __HAL_ADC_HPP__
