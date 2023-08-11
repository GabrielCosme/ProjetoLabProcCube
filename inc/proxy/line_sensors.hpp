
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
        LineSensors(HalAdc hal_adc);

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
