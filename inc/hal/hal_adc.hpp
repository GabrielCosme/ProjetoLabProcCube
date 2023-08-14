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
         * @brief Start the ADC conversion
         */
        void start_dma(void);

        /**
         * @brief Stop the ADC conversion
         */
        void stop_dma(void);

        /**
         * @brief Check if the ADC conversion is done
         *
         * @return true if the conversion is done, false otherwise
         */
        bool is_reading_done(void);

        /**
         * @brief Set the reading done object
         */
        static void set_reading_done(void);

        /**
         * @brief Update the ADC reading
         */
        void update_reading(void);

        /**
         * @brief Get the ADC reading
         *
         * @return the ADC reading
         */
        uint16_t get_adc_reading(uint8_t channel);

        /**
         * @brief Get the ADC reading array
         *
         * @return the ADC reading array
         */
        std::array<uint16_t, number_of_channels> get_adc_reading_array(void);

    private:
        ADC_HandleTypeDef* adc_handle;
        uint32_t buffer[number_of_channels * reading_per_channel];
        uint32_t buffer_size = number_of_channels * reading_per_channel;
        static bool reading_done;

        std::array<uint16_t, number_of_channels> adc_reading;

        void clear_adc_reading();

        void clear_buffer();

        void average_adc_reading();
};

#include "../src/hal/hal_adc.cpp"

#endif // __HAL_ADC_HPP__
