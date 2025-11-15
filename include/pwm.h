#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

typedef struct {
    uint32_t frequency_hz;
    float duty_cycle;
} pwm_config_t;

void PWM_Init(const pwm_config_t *config);
void PWM_SetDutyCycle(float duty_cycle);

#endif /* PWM_H_ */
