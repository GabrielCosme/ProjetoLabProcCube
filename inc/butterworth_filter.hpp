
#ifndef __BUTTERWORTH_SEC_ORDER_HPP__
#define __BUTTERWORTH_SEC_ORDER_HPP__

#include <array>

/*****************************************
 * Public Constants
 *****************************************/

constexpr uint8_t filter_order{2};

/*****************************************
 * Class Definition
 *****************************************/

/**
 * @brief Implementation of Butterworth second order low-pass filter
 *        A generic digital filter follows the relation
 *          a0 * y[k] = sum(bi * x[k - i]) - sum(aj * y[k - j])
 *        Where
 *          x[k] - measurement at instant k
 *          y[k] - filtered signal at instant k
 *        The Butterworth filter have the special property of being a
 *        maximally flat magnitude filter, in other words, is the best
 *        filter that doesn't present distortions around the cutoff
 *        frequency
 *        The formula for the continuos coefficients of the Butterworth
 *        filter is available here:
 *        https://en.wikipedia.org/wiki/Butterworth_filter
 *        The discrete version were computed with the Tustin method:
 *        https://en.wikipedia.org/wiki/Bilinear_transform
 */
class ButterworthFilter {
    public:
        /**
         * @brief Construct a new Butterworth Second Order filter object
         *
         * @param cutoff_frequency Low-pass cutoff frequency in Hz
         * @param sampling_frequency Sampling frequency in Hz.
         */
        ButterworthFilter(double cutoff_frequency, double sampling_frequency = 1.0);

        /**
         * @brief Produces a new value from measured data
         *
         * @param x0 Last measure
         *
         * @return Filtered value
         */
        double update(double x0);

    private:
        std::array<double, filter_order + 1> x_array;
        std::array<double, filter_order> y_array;

        std::array<double, filter_order + 1> b_array;
        std::array<double, filter_order> a_array;
};

#endif // __BUTTERWORTH_SEC_ORDER_HPP__