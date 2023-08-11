#include "hal/hal_adc.hpp"
#include "adc.h"

HalAdc::HalAdc(ADC_HandleTypeDef* adc_handle, uint8_t number_of_channels, uint16_t reading_per_channel) {
    MX_ADC1_Init();
    this->adc_handle = adc_handle;
    this->number_of_channels = number_of_channels;
    this->reading_per_channel = reading_per_channel;
    this->buffer = buffer;
    this->buffer_size = buffer_size;
    HalAdc::reading_done = false;
}

void HalAdc::start_dma(void) {
    HalAdc::reading_done = false;
    HAL_ADC_Start_DMA(this->adc_handle, this->buffer, this->buffer_size);
}

void HalAdc::stop_dma(void) {
    HAL_ADC_Stop_DMA(this->adc_handle);
}

bool HalAdc::is_reading_done(void) {
    return HalAdc::reading_done;
}

void HalAdc::set_reading_done(void) {
    HalAdc::reading_done = true;
}
