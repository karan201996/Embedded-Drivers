#include "control_loop.h"
#include "adc.h"
#include "pwm.h"
#include "system.h"
#include "tm4c123gh6pm.h"

static control_loop_config_t loop_cfg;
static float integrator = 0.0f;
static float sample_period = 0.0f;

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

void ControlLoop_Init(const control_loop_config_t *config)
{
    loop_cfg = *config;
    integrator = 0.0f;
    sample_period = 1.0f / (float)loop_cfg.sample_rate_hz;

    TIMER0_CTL_R &= ~TIMER_CTL_TAEN;
    TIMER0_CFG_R = 0u;
    TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;

    const uint32_t reload = (SystemCoreClockGet() / loop_cfg.sample_rate_hz) - 1u;
    TIMER0_TAILR_R = reload;
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    TIMER0_IMR_R |= TIMER_IMR_TATOIM;

    NVIC_PRI4_R = (NVIC_PRI4_R & ~NVIC_PRI4_TIMER0A_M) | (2u << NVIC_PRI4_TIMER0A_S);
    NVIC_EN0_R |= NVIC_EN0_TIMER0A;

    TIMER0_CTL_R |= TIMER_CTL_TAEN;
}

void ControlLoop_UpdateTarget(float voltage)
{
    loop_cfg.target_voltage = voltage;
}

void ControlLoop_TimerTick(void)
{
    const uint16_t raw = ADC_ReadBlocking();
    const float measured_voltage = ADC_ConvertToVoltage(raw);
    const float error = loop_cfg.target_voltage - measured_voltage;
    const float proportional = loop_cfg.kp * error;

    float new_integrator = integrator + loop_cfg.ki * error * sample_period;
    float command = proportional + new_integrator;
    float bounded = clamp(command, loop_cfg.min_duty, loop_cfg.max_duty);

    if (command != bounded) {
        new_integrator = bounded - proportional;
    }

    integrator = new_integrator;
    PWM_SetDutyCycle(bounded);
}

void Timer0A_Handler(void)
{
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    ControlLoop_TimerTick();
}
