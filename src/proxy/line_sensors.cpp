#include "hal/hal_adc.hpp"
#include "proxy/line_sensors.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define LINE_SENSOR_THRESHOLD 1000

#define LINE_SENSORS_NUMBER_OF_SENSORS 5
#define LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR 50

#define LINE_SENSORS_ADC_HANDLE hadc2
#define LINE_SENSORS_ADC_BUFFER_SIZE (LINE_SENSORS_NUMBER_OF_SENSORS * LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR)

const float SENSORS_WEIGHT[] = {2.0, 1.0, 0.0, -1.0, -2.0};

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

LineSensors::LineSensors() : hal_adc(line_sensor_adc_handle, adc_num_channels, adc_readings_per_channel) {
    hal_adc.start_dma();
}

void LineSensors::update_reading() {
    if (!hal_adc.is_reading_done()) {
        return;
    }

    hal_adc.stop_dma();
}

void clear_adc_reading() {
    for (uint8_t i = 0; i < LINE_SENSORS_NUMBER_OF_SENSORS; i++) {
        m_adc_reading[i] = 0;
    }
}

void clear_adc_reading() {
}

void average_adc_reading() {
}

void line_sensors_init() {
    HAL_ADC_Start_DMA(&LINE_SENSORS_ADC_HANDLE, m_adc_buffer, LINE_SENSORS_ADC_BUFFER_SIZE);
}

void line_sensors_update_reading() {
    if (!m_finished_reading) {
        return;
    }

    HAL_ADC_Stop_DMA(&LINE_SENSORS_ADC_HANDLE);

    // Clear old readings
    for (uint8_t i = 0; i < LINE_SENSORS_NUMBER_OF_SENSORS; i++) {
        m_adc_reading[i] = 0;
    }

    // Average readings
    for (uint8_t i = 0; i < LINE_SENSORS_NUMBER_OF_SENSORS; i++) {
        for (uint16_t j = 0; j < LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR; j++) {
            m_adc_reading[i] += m_adc_buffer[LINE_SENSORS_NUMBER_OF_SENSORS * j + i];
        }

        m_adc_reading[i] /= LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR;
    }

    // Clear buffer
    for (uint8_t i = 0; i < LINE_SENSORS_ADC_BUFFER_SIZE; i++) {
        m_adc_buffer[i] = 0;
    }

    m_finished_reading = false;

    HAL_ADC_Start_DMA(&LINE_SENSORS_ADC_HANDLE, m_adc_buffer, LINE_SENSORS_ADC_BUFFER_SIZE);
}

uint32_t line_sensors_get_reading(uint8_t sensor) {
    if (sensor >= LINE_SENSORS_NUMBER_OF_SENSORS) {
        return 0;
    }

    return m_adc_reading[sensor];
}

float line_sensors_get_position() {
    float position = 0;
    uint8_t active_sensors = 0;

    for (uint8_t i = 0; i < LINE_SENSORS_NUMBER_OF_SENSORS; i++) {
        if (m_adc_reading[i] < LINE_SENSOR_THRESHOLD) {
            position += SENSORS_WEIGHT[i];
            active_sensors++;
        }
    }

    if (active_sensors > 0) {
        position /= active_sensors;
    }

    return position;
}
