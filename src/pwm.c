#include "pwm.h"
#include "system.h"
#include "tm4c123gh6pm.h"

#ifndef PWM_MIN_DUTY
#define PWM_MIN_DUTY 0.02f
#endif

#ifndef PWM_MAX_DUTY
#define PWM_MAX_DUTY 0.95f
#endif

static uint32_t pwm_load_value = 0u;

static float clamp(float value, float min, float max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

void PWM_Init(const pwm_config_t *config)
{
    const uint32_t pwm_clock = SystemCoreClockGet() / 2u;
    GPIO_PORTB_AFSEL_R |= (1u << 6);
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~(0xFu << 24)) | (0x4u << 24);
    GPIO_PORTB_DEN_R |= (1u << 6);
    GPIO_PORTB_AMSEL_R &= ~(1u << 6);

    PWM0_0_CTL_R = 0u;
    PWM0_CTL_R = 0u;

    pwm_load_value = (pwm_clock / config->frequency_hz) - 1u;
    PWM0_0_LOAD_R = pwm_load_value;
    PWM0_0_GENA_R = 0x0000008Cu; /* set output high at load, low at comparator */

    PWM_SetDutyCycle(config->duty_cycle);

    PWM0_0_CTL_R |= 0x1u;
    PWM0_ENABLE_R |= 0x1u;
}

void PWM_SetDutyCycle(float duty_cycle)
{
    const float bounded = clamp(duty_cycle, PWM_MIN_DUTY, PWM_MAX_DUTY);
    const float comparator_fraction = 1.0f - bounded;
    const uint32_t cmp_value = (uint32_t)((float)(pwm_load_value + 1u) * comparator_fraction);

    if (pwm_load_value == 0u) {
        return;
    }

    PWM0_0_CMPA_R = cmp_value;
}
