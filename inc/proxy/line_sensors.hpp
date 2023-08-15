
#ifndef __LINE_SENSORS_HPP__
#define __LINE_SENSORS_HPP__

#include <array>

#include "hal/hal_adc.hpp"

/*****************************************
 * Public Functions Prototypes
 *****************************************/

template <uint8_t number_of_sensors, uint16_t reading_per_sensor>
class LineSensors {
    public:
        /**
         * @brief Construct a new Line Sensors object
         *
         * @param adc_handle Handle to the ADC
         */
        LineSensors(ADC_HandleTypeDef* adc_handle);

        /**
         * @brief Gets the line position.
         *
         * @return Position of the line.
         */
        float get_position();

        /**
         * @brief Calibrates the line sensors for the white line
         */
        void calibrate_white();

        /**
         * @brief Calibrates the line sensors for the black background
         */
        void calibrate_black();

    private:
        HalAdc<number_of_sensors, reading_per_sensor> hal_adc;

        std::array<float, number_of_sensors> sensors_weight;

        std::array<uint32_t, number_of_sensors> white_readings;

        std::array<uint32_t, number_of_sensors> black_readings;

        std::array<uint32_t, number_of_sensors> line_thresholds;
};

#include "../src/proxy/line_sensors.cpp"

#endif // __LINE_SENSORS_HPP__
