#include "butterworth_filter.hpp"
#include "mcu.h"
#include "proxy/button.hpp"
#include "proxy/line_sensors.hpp"
#include "proxy/locomotion.hpp"
#include "pid_controller.hpp"

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    Button button(button_gpio_port, button_pin);

    HalGpio led(led_gpio_port, led_pin);

    LineSensors line_sensors();

    Locomotion locomotion();

    PidController pid_controller(kp, ki, kd, saturation, max_integral);

    ButterworthFilter filter(filter_frequency);

    bool stopped = true;
    float angular_position = 0, line_measure = 0;
    uint16_t angular_command = 0;
    uint16_t linear_command = 0;

    for (;;) {
        if (button.get_status() != BUTTON_NO_PRESS) {
            stopped = !stopped;
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
