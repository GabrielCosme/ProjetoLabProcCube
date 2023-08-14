
#ifndef __LINE_SENSORS_HPP__
#define __LINE_SENSORS_HPP__

#include <array>

#include "hal/hal_adc.hpp"

static constexpr uint8_t number_of_sensors = 8;

/*****************************************
 * Public Functions Prototypes
 *****************************************/

class LineSensors {
    public:
        /**
         * @brief Construct a new Line Sensors object
         *
         * @param adc_handle Handle to the ADC
         * @param number_of_channels Number of channels of the ADC
         * @param reading_per_channel Number of readings per channel
         */
        LineSensors(ADC_HandleTypeDef* adc_handle, uint8_t number_of_channels, uint16_t reading_per_channel);

        /**
         * @brief Updates the line sensors readings.
         */
        void update_reading();

        /**
         * @brief Gets the line position.
         *
         * @return Position of the line.
         */
        float get_position();

    private:
        HalAdc hal_adc;

        std::array<uint16_t, number_of_sensors> line_threshold;
};

#endif // __LINE_SENSORS_HPP__
