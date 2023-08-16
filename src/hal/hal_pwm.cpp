#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/gpio.h>

#include "hal/hal_pwm.hpp"

HalPwm::HalPwm(const PwmConfig& pwm_config) {
    this->channel = channel;

    rcc_periph_clock_enable(pwm_config.gpio.rcc_clock);
    rcc_periph_clock_enable(pwm_config.rcc_timer_clock);

    gpio_mode_setup(pwm_config.gpio.port, pwm_config.gpio.mode, pwm_config.gpio.pull_up_down, pwm_config.gpio.pin);
    gpio_set_af(pwm_config.gpio.port, GPIO_AF1, pwm_config.gpio.pin);

    timer_enable_preload(pwm_config.timer);
    timer_enable_oc_preload(pwm_config.timer, pwm_config.oc_id);
    timer_set_counter(pwm_config.timer, pwm_config.period * 1 / 4);
    timer_set_oc_mode(pwm_config.timer, pwm_config.oc_id, pwm_config.oc_mode);
    timer_set_oc_value(pwm_config.timer, pwm_config.oc_id, pwm_config.period * 1 / 4);
    timer_enable_oc_output(pwm_config.timer, pwm_config.oc_id);
    timer_set_period(pwm_config.timer, pwm_config.period);

    // timer_set_prescaler();
    timer_continuous_mode(pwm_config.timer);
    timer_generate_event(pwm_config.timer, TIM_EGR_UG);
    timer_enable_counter(pwm_config.timer);
    timer_enable_irq(pwm_config.timer, TIM_DIER_COMIE);
    nvic_enable_irq(pwm_config.irqn);
}

void HalPwm::set_compare(uint32_t compare) {
    timer_set_oc_value(this->timer_handle, this->channel, compare);
}
