#include "hal/hal_adc.h"
#include "adc.h"  // apagar

void hal_adc_init(void) {
    MX_ADC1_Init();
}

void hal_adc_start_dma(uint32_t* buffer, uint32_t buffer_size) {
    HAL_ADC_Start_DMA(&hadc1, buffer, buffer_size);
}

void hal_adc_stop_dma(void) {
    HAL_ADC_Stop_DMA(&hadc1);
}

void hal_adc_callback(void) {
}
