#include "system.h"
#include "pwm.h"
#include "adc.h"
#include "control_loop.h"

int main(void)
{
    const pwm_config_t pwm_cfg = {
        .frequency_hz = 200000u,
        .duty_cycle = 0.5f,
    };
    PWM_Init(&pwm_cfg);

    const adc_config_t adc_cfg = {
        .channel = 0u,
        .reference_voltage = 3.3f,
    };
    ADC_Init(&adc_cfg);

    const control_loop_config_t loop_cfg = {
        .target_voltage = 2.0f,
        .kp = 0.08f,
        .ki = 500.0f,
        .min_duty = 0.05f,
        .max_duty = 0.90f,
        .sample_rate_hz = 40000u,
    };
    ControlLoop_Init(&loop_cfg);

    __asm volatile("cpsie i");

    while (1) {
        __asm volatile("wfi");
    }
}
