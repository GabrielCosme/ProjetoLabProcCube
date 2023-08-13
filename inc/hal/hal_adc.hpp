#ifndef __HAL_ADC_HPP__
#define __HAL_ADC_HPP__

#include <cstdint>

#include "adc.h"

/*****************************************
 * Class Declaration
 *****************************************/

class HalAdc {
    public:
        /**
         * @brief Construct a new Hal Adc object
         *
         * @param adc_handle pointer to the ADC handle
         * @param number_of_channels number of channels
         * @param reading_per_channel number of reading per channel
         */
        HalAdc(ADC_HandleTypeDef* adc_handle, uint8_t number_of_channels, uint16_t reading_per_channel);

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

    private:
        ADC_HandleTypeDef* adc_handle;
        uint32_t* buffer;
        uint32_t buffer_size;
        uint8_t number_of_channels;
        uint16_t reading_per_channel;
        static bool reading_done;

        // std::array<uint16_t, number_of_sensors> adc_reading;

        // void clear_adc_reading();

        // void clear_adc_reading();

        // void average_adc_reading();
};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    (void) (hadc);
    HalAdc::set_reading_done();
};

#endif // __HAL_ADC_HPP__
