#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

#include "stdint.h"

void hal_adc_init(void);

void hal_adc_start_dma(uint32_t* buffer, uint32_t buffer_size);

void hal_adc_stop_dma(void);

void hal_adc_callback(void);

#endif // __HAL_ADC_H__
