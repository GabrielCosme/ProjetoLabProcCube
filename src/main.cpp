#include "butterworth_filter.hpp"
#include "mcu.h"
#include "proxy/button.hpp"
#include "proxy/line_sensors.hpp"
#include "proxy/locomotion.hpp"
#include "pid_controller.hpp"

/*****************************************
 * Private Constant Definitions
 *****************************************/

static constexpr uint16_t linear_setpoint = 50;
static constexpr float linear_decay = 0.5;

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();

    Button button(BUTTON_GPIO_Port, BUTTON_Pin);

    LineSensors line_sensors();

    Locomotion locomotion();

    PidController pid_controller(0.5, 0.5, 0.5);

    ButterworthFilter filter(0.5);

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

        linear_command = Locomotion::linear_decay(angular_position, linear_decay) * linear_setpoint;

        locomotion.set_speeds(linear_command, angular_command);
    }
}
