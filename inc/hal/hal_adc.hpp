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

template <uint8_t number_of_channels, uint16_t reading_per_channel>
HalAdc<number_of_channels, reading_per_channel>::HalAdc(ADC_HandleTypeDef* adc_handle) {
    MX_ADC1_Init();
    this->adc_handle = adc_handle;

    // HalAdc::reading_done = false;
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::start_dma(void) {
    // HalAdc::reading_done = false;
    HAL_ADC_Start_DMA(this->adc_handle, this->buffer, this->buffer_size);
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::stop_dma(void) {
    HAL_ADC_Stop_DMA(this->adc_handle);
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
bool HalAdc<number_of_channels, reading_per_channel>::is_reading_done(void) {
    return HalAdc::reading_done;
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::set_reading_done(void) {
    HalAdc::reading_done = true;
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::update_reading(void) {
    if (!this->is_reading_done()) {
        return;
    }

    this->stop_dma();

    this->clear_adc_reading();
    this->average_adc_reading();
    this->clear_buffer();

    this->start_dma();
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
uint16_t HalAdc<number_of_channels, reading_per_channel>::get_adc_reading(uint8_t channel) {
    return this->adc_reading[channel];
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
std::array<uint16_t, number_of_channels> HalAdc<number_of_channels, reading_per_channel>::get_adc_reading_array(void) {
    return this->adc_reading;
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::clear_adc_reading() {
    this->adc_reading.fill(0);
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::clear_buffer() {
    for (uint8_t i = 0; i < this->buffer_size; i++) {
        this->buffer[i] = 0;
    }
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::average_adc_reading() {
    for (uint8_t i = 0; i < number_of_channels; i++) {
        for (uint16_t j = 0; j < reading_per_channel; j++) {
            this->adc_reading[i] += this->buffer[number_of_channels * j + i];
        }

        this->adc_reading[i] /= reading_per_channel;
    }
}

#endif // __HAL_ADC_HPP__
