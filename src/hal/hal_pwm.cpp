#include "hal/hal_pwm.hpp"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

HalPwm::HalPwm(const PwmConfig& pwm_config) {
    this->timer_handle = timer_handle;
    this->channel = channel;

    // exemple GPIOA11
    rcc_periph_clock_enable(RCC_GPIOA);                           // enable GPIOA clock
    rcc_periph_clock_enable(RCC_TIM1);                            // enable TIM1 clock
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11); // pin PA11 Alt Function
    gpio_set_af(GPIOA, GPIO_AF1, GPIO11);
}

void HalPwm::start(void) {
    HAL_TIM_PWM_Start(this->timer_handle, this->channel);
}

void HalPwm::set_compare(uint32_t compare) {
    __HAL_TIM_SET_COMPARE(this->timer_handle, this->channel, compare);
}

#define LED PC13
const uint32_t timer_peri = TIM1;     // timer peripheral
const enum tim_oc_id oc_id = TIM_OC4; // output compare channel designator
const uint32_t period = 1000;         // counter in clock ticks

int main(void) {
    // pin_out(LED);

    // setup PA11 for PWM
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM1);                            // enable TIM1 clock
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11); // pin PA11 Alt Function
    gpio_set_af(GPIOA, GPIO_AF1, GPIO11);

    // timer_reset(timer_peri);
    timer_enable_preload(TIM1);  // causes counter to be loaded from its ARR only at next update event
    timer_enable_oc_preload(TIM1, TIM_OC4);
    timer_set_counter(TIM1, period * 1 / 4);           // set duty cycle to 25%
    timer_set_oc_mode(TIM1, TIM_OC4, TIM_OCM_PWM1);    // output active when counter is lt compare register
    timer_set_oc_value(TIM1, TIM_OC4, period * 1 / 4); // set duty cycle to 25%
    timer_enable_oc_output(TIM1, TIM_OC4);             // enable timer output compare
    timer_set_period(TIM1, period);                    // set the timer period in the auto-reload register

    // timer_set_prescaler();
    timer_continuous_mode(TIM1);  // enable the timer to run continuously
    timer_generate_event(TIM1, TIM_EGR_UG);
    timer_enable_counter(TIM1);
    timer_enable_irq(TIM1, TIM_DIER_COMIE);  // enable commutation interrupt
    nvic_enable_irq(NVIC_TIM1_CC_IRQ);

    while (1) {
        pin_toggle(LED);
        mal_delayish(100);
    }
}
