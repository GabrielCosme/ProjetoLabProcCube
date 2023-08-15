#ifndef __HAL_ADC_CPP__
#define __HAL_ADC_CPP__

#include "hal/hal_adc.hpp"
#include "adc.h"
#include "dma.h"

template <uint8_t number_of_channels, uint16_t reading_per_channel>
bool HalAdc<number_of_channels, reading_per_channel>::reading_done = false;

template <uint8_t number_of_channels, uint16_t reading_per_channel>
HalAdc<number_of_channels, reading_per_channel>::HalAdc(ADC_HandleTypeDef* adc_handle) {
    MX_DMA_Init();
    MX_ADC1_Init();

    this->adc_handle = adc_handle;
    HalAdc::reading_done = false;

    HAL_ADC_Start_DMA(this->adc_handle, this->buffer, this->buffer_size);
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::update_reading(void) {
    if (not HalAdc::reading_done) {
        return;
    }

    HAL_ADC_Stop_DMA(this->adc_handle);
    this->adc_reading.fill(0);

    for (uint8_t i = 0; i < number_of_channels; i++) {
        for (uint16_t j = 0; j < reading_per_channel; j++) {
            this->adc_reading[i] += this->buffer[number_of_channels * j + i];
        }

        this->adc_reading[i] /= reading_per_channel;
    }

    for (uint16_t i = 0; i < this->buffer_size; i++) {
        this->buffer[i] = 0;
    }

    HAL_ADC_Start_DMA(this->adc_handle, this->buffer, this->buffer_size);
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
uint32_t HalAdc<number_of_channels, reading_per_channel>::get_adc_reading(uint8_t channel) const {
    return this->adc_reading[channel];
}

template <uint8_t number_of_channels, uint16_t reading_per_channel>
void HalAdc<number_of_channels, reading_per_channel>::set_reading_done(void) {
    HalAdc::reading_done = true;
}

#endif // __HAL_ADC_CPP__
