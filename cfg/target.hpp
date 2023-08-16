#ifndef __TARGET_HPP__
#define __TARGET_HPP__

#include "hal/hal_gpio.hpp"
#include "proxy/motor.hpp"

constexpr GpioConfig button_config = {
    .port = GPIOB,
    .mode = GPIO_MODE_INPUT,
    .pull_resistor = GPIO_PUPD_PULLUP,
    .pin = GPIO10,
    .rcc_clock = RCC_GPIOB,
};

constexpr GpioConfig led_config = {
    .port = GPIOB,
    .mode = GPIO_MODE_OUTPUT,
    .pull_resistor = GPIO_PUPD_NONE,
    .pin = GPIO15,
    .rcc_clock = RCC_GPIOB,
};

constexpr MotorConfig left_motor_config = {
    .forward_pwm = {
        .gpio = {
            .port = GPIOA,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .pin = GPIO11,
            .rcc_clock = RCC_GPIOA,
        },
        .rcc_timer_clock = RCC_TIM1,
        .timer = TIM1,
        .period = 1000,
        .oc_id = TIM_OC1,
        .oc_mode = TIM_OCM_PWM1,
        .irqn = NVIC_TIM1_CC_IRQ,
    },
    .backward_pwm = {
        .gpio = {
            .port = GPIOA,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .pin = GPIO12,
            .rcc_clock = RCC_GPIOA,
        },
        .rcc_timer_clock = RCC_TIM1,
        .timer = TIM1,
        .period = 1000,
        .oc_id = TIM_OC2,
        .oc_mode = TIM_OCM_PWM1,
        .irqn = NVIC_TIM1_CC_IRQ,
    },
};

constexpr MotorConfig right_motor_config = {
    .forward_pwm = {
        .gpio = {
            .port = GPIOA,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .pin = GPIO8,
            .rcc_clock = RCC_GPIOA,
        },
        .rcc_timer_clock = RCC_TIM2,
        .timer = TIM2,
        .period = 1000,
        .oc_id = TIM_OC1,
        .oc_mode = TIM_OCM_PWM1,
        .irqn = NVIC_TIM2_CC_IRQ,
    },
    .backward_pwm = {
        .gpio = {
            .port = GPIOA,
            .mode = GPIO_MODE_AF,
            .pull_resistor = GPIO_PUPD_NONE,
            .pin = GPIO9,
            .rcc_clock = RCC_GPIOA,
        },
        .rcc_timer_clock = RCC_TIM2,
        .timer = TIM2,
        .period = 1000,
        .oc_id = TIM_OC2,
        .oc_mode = TIM_OCM_PWM1,
        .irqn = NVIC_TIM2_CC_IRQ,
    },
};

AdcConfig line_sensors_config = {
};

ADC_HandleTypeDef* line_sensor_adc_handle = &hadc1;
constexpr uint8_t adc_num_channels = 8;
constexpr uint16_t adc_readings_per_channel = 50;

#endif // __TARGET_HPP__
