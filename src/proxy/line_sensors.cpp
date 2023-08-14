// #include "hal/hal_adc.hpp"
// #include "proxy/line_sensors.hpp"

///*****************************************
// * Private Constants
// *****************************************/

// #define LINE_SENSOR_THRESHOLD 1000

// #define LINE_SENSORS_NUMBER_OF_SENSORS 5
// #define LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR 50

// #define LINE_SENSORS_ADC_HANDLE hadc2
// #define LINE_SENSORS_ADC_BUFFER_SIZE (LINE_SENSORS_NUMBER_OF_SENSORS * LINE_SENSORS_NUMBER_OF_READINGS_PER_SENSOR)

// const float SENSORS_WEIGHT[] = {2.0, 1.0, 0.0, -1.0, -2.0};

///*****************************************
// * Public Functions Bodies Definitions
// *****************************************/

// template <uint8_t number_of_sensors, uint16_t reading_per_sensor>
// LineSensors<number_of_sensors, reading_per_sensor>::LineSensors(ADC_HandleTypeDef* adc_handle) :
// hal_adc(adc_handle) {
// hal_adc.start_dma();
// }

// template <uint8_t number_of_sensors, uint16_t reading_per_sensor>
// void LineSensors<number_of_sensors, reading_per_sensor>::update_reading() {
// hal_adc.update_reading();
// }

// template <uint8_t number_of_sensors, uint16_t reading_per_sensor>
// float LineSensors<number_of_sensors, reading_per_sensor>::get_position() {
// float position = 0;
// uint8_t active_sensors = 0;

// for (uint8_t i = 0; i < number_of_sensors; i++) {
// if (this->hal_adc.get_adc_reading(i) < LINE_SENSOR_THRESHOLD) {
// position += SENSORS_WEIGHT[i];
// active_sensors++;
// }
// }

// if (active_sensors > 0) {
// position /= active_sensors;
// }

// return position;
// }
