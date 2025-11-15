#include "system.h"
#include "tm4c123gh6pm.h"

static uint32_t system_clock_hz = 16000000u;

void SystemClock_Config(void)
{
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;

    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;
    SYSCTL_RCC_R &= ~SYSCTL_RCC_SYSDIV_M;

    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
    SYSCTL_RCC2_R |= SYSCTL_RCC2_OSCSRC2_MO;
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;

    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;
    SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV;
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~SYSCTL_RCC2_SYSDIV2_M) |
                    (4u << SYSCTL_RCC2_SYSDIV2_S);

    while ((SYSCTL_RIS_R & SYSCTL_RIS_PLLLRIS) == 0u) {
    }

    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;

    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M;
    SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV | SYSCTL_RCC_PWMDIV_2;

    system_clock_hz = 80000000u;
}

void System_EnableModuleClocks(void)
{
    SYSCTL_RCGCGPIO_R |= (1u << 1); /* Port B */
    SYSCTL_RCGCGPIO_R |= (1u << 4); /* Port E */
    while ((SYSCTL_PRGPIO_R & (1u << 1)) == 0u) {
    }
    while ((SYSCTL_PRGPIO_R & (1u << 4)) == 0u) {
    }

    SYSCTL_RCGCPWM_R |= (1u << 0); /* PWM0 */
    while ((SYSCTL_PRPWM_R & (1u << 0)) == 0u) {
    }

    SYSCTL_RCGCADC_R |= (1u << 0); /* ADC0 */
    while ((SYSCTL_PRADC_R & (1u << 0)) == 0u) {
    }

    SYSCTL_RCGCTIMER_R |= (1u << 0); /* Timer0 */
    while ((SYSCTL_PRTIMER_R & (1u << 0)) == 0u) {
    }
}

void SystemInit(void)
{
    SystemClock_Config();
    System_EnableModuleClocks();
}

uint32_t SystemCoreClockGet(void)
{
    return system_clock_hz;
}
