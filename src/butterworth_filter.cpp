#include <cmath>

#include "butterworth_filter.hpp"

/*****************************************
 * Private Constants
 *****************************************/

/**
 * @brief Max relation between frequency and sampling frequency
 *        (frequency / sampling_frequency) required by the
 *        Nyquist-Shannon sampling theorem
 */
static constexpr double nyquist_freq_relat{0.5};

/*****************************************
 * Class Methods Bodies Definitions
 *****************************************/

ButterworthFilter::ButterworthFilter(double cutoff_frequency, double sampling_frequency) :
    x_array{}, y_array{}, a_array{}, b_array{} {
    double freq_relat = cutoff_frequency / sampling_frequency;

    ROS_WARN_STREAM_COND(freq_relat > nyquist_freq_relat, "Filter cutoff frequency larger than Nyquist frequency");  // NOLINT

    double b0 = 1;
    double b1 = 2;
    double b2 = 1;

    // Butterworth filter coefficients
    double a0 = 1 + 2 * std::sqrt(2) / freq_relat + 4 / std::pow(freq_relat, 2); // NOLINT
    double a1 = 2 - 8 / std::pow(freq_relat, 2);                                 // NOLINT
    double a2 = 1 - 2 * std::sqrt(2) / freq_relat + 4 / std::pow(freq_relat, 2); // NOLINT

    this->a_array[0] = a2 / a0;
    this->a_array[1] = a1 / a0;

    this->b_array[0] = b2 / a0;
    this->b_array[1] = b1 / a0;
    this->b_array[2] = b0 / a0;
}

double ButterworthFilter::update(double x0) {
    this->x_array[0] = this->x_array[1];
    this->x_array[1] = this->x_array[2];
    this->x_array[2] = x0;

    double x_b_dot = 0;

    for (int i = 0; i < filter_order + 1; i++) {
        x_b_dot += this->x_array[i] * this->b_array[i];
    }

    double y_a_dot = 0;

    for (int i = 0; i < filter_order; i++) {
        y_a_dot += this->y_array[i] * this->a_array[i];
    }

    double y0 = x_b_dot - y_a_dot;

    this->y_array[0] = this->y_array[1];
    this->y_array[1] = y0;

    return y0;
}
