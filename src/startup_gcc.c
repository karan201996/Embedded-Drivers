#include <stdint.h>

extern int main(void);
extern void SystemInit(void);
extern void Timer0A_Handler(void);

void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOPortA_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOPortB_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOPortC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOPortD_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOPortE_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SSI0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM0Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM0Generator0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM0Generator1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM0Generator2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void QEI0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC0Seq0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC0Seq1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC0Seq2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC0Seq3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Watchdog_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Timer0B_Handler(void) __attribute__((weak, alias("Default_Handler")));

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    (void *)&_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    GPIOPortA_Handler,
    GPIOPortB_Handler,
    GPIOPortC_Handler,
    GPIOPortD_Handler,
    GPIOPortE_Handler,
    UART0_Handler,
    UART1_Handler,
    SSI0_Handler,
    I2C0_Handler,
    PWM0Fault_Handler,
    PWM0Generator0_Handler,
    PWM0Generator1_Handler,
    PWM0Generator2_Handler,
    QEI0_Handler,
    ADC0Seq0_Handler,
    ADC0Seq1_Handler,
    ADC0Seq2_Handler,
    ADC0Seq3_Handler,
    Watchdog_Handler,
    Timer0A_Handler,
    Timer0B_Handler,
};

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata) {
        *dst++ = *src++;
    }

    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0u;
    }

    SystemInit();
    (void)main();

    while (1) {
    }
}

void Default_Handler(void)
{
    while (1) {
    }
}
