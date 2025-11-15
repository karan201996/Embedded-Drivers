#ifndef CONTROL_LOOP_H_
#define CONTROL_LOOP_H_

#include <stdint.h>

typedef struct {
    float target_voltage;
    float kp;
    float ki;
    float min_duty;
    float max_duty;
    uint32_t sample_rate_hz;
} control_loop_config_t;

void ControlLoop_Init(const control_loop_config_t *config);
void ControlLoop_TimerTick(void);
void ControlLoop_UpdateTarget(float voltage);

#endif /* CONTROL_LOOP_H_ */
