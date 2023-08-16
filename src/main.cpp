#include "mcu.hpp"

#include "constants.hpp"
#include "target.hpp"

#include "butterworth_filter.hpp"
#include "pid_controller.hpp"

#include "proxy/button.hpp"
#include "proxy/line_sensors.hpp"
#include "proxy/locomotion.hpp"

int main(void) {
    mcu_init();

    Button button(button_config);

    HalGpio led(led_config);

    LineSensors<adc_num_channels> line_sensors(line_sensors_config);

    Locomotion locomotion(left_motor_config, right_motor_config, left_deadzone, right_deadzone);

    PidController pid_controller(kp, ki, kd, 0.0, saturation, max_integral);

    ButterworthFilter filter(filter_frequency);

    led.write(true);

    bool stopped = true;
    float angular_position = 0, line_measure = 0;
    int16_t angular_command = 0;
    int16_t linear_command = 0;

    for (;;) {
        button_status_t button_status = button.get_status();

        if (button_status == BUTTON_LONG_PRESS) {
            line_sensors.calibrate_white();
        } else if (button_status == BUTTON_EXTRA_LONG_PRESS) {
            line_sensors.calibrate_black();
        } else if (button_status == BUTTON_SHORT_PRESS) {
            stopped = not stopped;
            led.toggle();
        }

        if (stopped) {
            locomotion.set_speeds(0, 0);
            pid_controller.reset();
            filter.update(0);
            continue;
        }

        line_measure = line_sensors.get_position();
        angular_position = filter.update(line_measure);
        angular_command = pid_controller.update(angular_position);

        linear_command = Locomotion::linear_decay(angular_position, linear_decay) * linear_base_speed;

        locomotion.set_speeds(linear_command, angular_command);
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    (void) (hadc);
    HalAdc<adc_num_channels, adc_readings_per_channel>::set_reading_done();
};
