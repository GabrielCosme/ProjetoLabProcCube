#ifndef __LINE_SENSORS_CPP__
#define __LINE_SENSORS_CPP__

#include "hal/hal_adc.hpp"
#include "proxy/line_sensors.hpp"

/*****************************************
 * Private Constants
 *****************************************/

constexpr uint16_t LINE_SENSOR_THRESHOLD = 1000;

constexpr float SENSORS_WEIGHT[] = {5.0, 4.0, 3.0, 2.0, 1.0, -1.0, -2.0, -3.0, -4.0, -5.0};

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

template <uint8_t number_of_sensors, uint16_t reading_per_sensor>
LineSensors<number_of_sensors, reading_per_sensor>::LineSensors(ADC_HandleTypeDef* adc_handle) :
    hal_adc(adc_handle) {
    hal_adc.start_dma();
}

template <uint8_t number_of_sensors, uint16_t reading_per_sensor>
float LineSensors<number_of_sensors, reading_per_sensor>::get_position() {
    hal_adc.update_reading();

    float position = 0;
    uint8_t active_sensors = 0;

    for (uint8_t i = 0; i < number_of_sensors; i++) {
        if (this->hal_adc.get_adc_reading(i) < LINE_SENSOR_THRESHOLD) {
            position += SENSORS_WEIGHT[i];
            active_sensors++;
        }
    }

    if (active_sensors > 0) {
        position /= active_sensors;
    }

    return position;
}

#endif // __LINE_SENSORS_CPP__
