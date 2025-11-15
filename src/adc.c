#include "adc.h"
#include "tm4c123gh6pm.h"

static float adc_reference_voltage = 3.3f;

static void configure_analog_input(uint8_t channel)
{
    if (channel <= 3u) {
        const uint8_t pin = (uint8_t)(3u - channel);
        GPIO_PORTE_AFSEL_R |= (1u << pin);
        GPIO_PORTE_DEN_R &= ~(1u << pin);
        GPIO_PORTE_AMSEL_R |= (1u << pin);
    }
}

void ADC_Init(const adc_config_t *config)
{
    adc_reference_voltage = config->reference_voltage;

    configure_analog_input(config->channel);

    ADC0_ACTSS_R &= ~(1u << 3); /* disable sample sequencer 3 */
    ADC0_SSPRI_R = (ADC0_SSPRI_R & ~0xFFFFu) | ADC_SSPRI_SS3_0;
    ADC0_PC_R = 0x1u;
    ADC0_EMUX_R &= ~(0xFu << 12); /* processor trigger */
    ADC0_SSMUX3_R = config->channel;
    ADC0_SSCTL3_R = ADC_SSCTL3_IE | ADC_SSCTL3_END;
    ADC0_IM_R &= ~(1u << 3);
    ADC0_ACTSS_R |= (1u << 3);
}

uint16_t ADC_ReadBlocking(void)
{
    ADC0_PSSI_R |= (1u << 3);
    while ((ADC0_RIS_R & (1u << 3)) == 0u) {
    }
    const uint16_t sample = (uint16_t)ADC0_SSFIFO3_R;
    ADC0_ISC_R |= (1u << 3);
    return sample;
}

float ADC_ConvertToVoltage(uint16_t sample)
{
    return ((float)sample / 4095.0f) * adc_reference_voltage;
}
