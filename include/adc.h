#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef struct {
    uint8_t channel;
    float reference_voltage;
} adc_config_t;

void ADC_Init(const adc_config_t *config);
uint16_t ADC_ReadBlocking(void);
float ADC_ConvertToVoltage(uint16_t sample);

#endif /* ADC_H_ */
