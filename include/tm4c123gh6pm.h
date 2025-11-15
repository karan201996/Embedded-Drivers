#ifndef TM4C123GH6PM_H_
#define TM4C123GH6PM_H_

#include <stdint.h>

#define HWREG(x) (*((volatile uint32_t *)(x)))

/* System Control */
#define SYSCTL_RIS_R              HWREG(0x400FE050)
#define SYSCTL_RCC_R              HWREG(0x400FE060)
#define SYSCTL_RCC2_R             HWREG(0x400FE070)
#define SYSCTL_RCGCGPIO_R         HWREG(0x400FE608)
#define SYSCTL_PRGPIO_R           HWREG(0x400FEA08)
#define SYSCTL_RCGCPWM_R          HWREG(0x400FE640)
#define SYSCTL_RCGCADC_R          HWREG(0x400FE638)
#define SYSCTL_RCGCTIMER_R        HWREG(0x400FE604)
#define SYSCTL_PRPWM_R            HWREG(0x400FEA60)
#define SYSCTL_PRADC_R            HWREG(0x400FEA38)
#define SYSCTL_PRTIMER_R          HWREG(0x400FEA04)

#define SYSCTL_RCC_XTAL_M         0x000007C0
#define SYSCTL_RCC_XTAL_16MHZ     0x00000540
#define SYSCTL_RCC_OSCSRC_MAIN    0x00000000
#define SYSCTL_RCC_PWRDN          0x00002000
#define SYSCTL_RCC_USESYSDIV      0x00400000
#define SYSCTL_RCC_SYSDIV_M       0x07800000
#define SYSCTL_RCC_SYSDIV_S       23
#define SYSCTL_RCC_USEPWMDIV      0x00100000
#define SYSCTL_RCC_PWMDIV_M       0x000E0000
#define SYSCTL_RCC_PWMDIV_2       0x00000000

#define SYSCTL_RCC2_USERCC2       0x80000000
#define SYSCTL_RCC2_DIV400        0x40000000
#define SYSCTL_RCC2_OSCSRC2_M     0x00000070
#define SYSCTL_RCC2_OSCSRC2_MO    0x00000000
#define SYSCTL_RCC2_PWRDN2        0x00002000
#define SYSCTL_RCC2_BYPASS2       0x00000800
#define SYSCTL_RCC2_SYSDIV2_M     0x1FC00000
#define SYSCTL_RCC2_SYSDIV2_S     22
#define SYSCTL_RIS_PLLLRIS        0x00000040

/* GPIO Port B */
#define GPIO_PORTB_BASE           0x40005000
#define GPIO_PORTB_DIR_R          HWREG(GPIO_PORTB_BASE + 0x400)
#define GPIO_PORTB_AFSEL_R        HWREG(GPIO_PORTB_BASE + 0x420)
#define GPIO_PORTB_DEN_R          HWREG(GPIO_PORTB_BASE + 0x51C)
#define GPIO_PORTB_PCTL_R         HWREG(GPIO_PORTB_BASE + 0x52C)
#define GPIO_PORTB_AMSEL_R        HWREG(GPIO_PORTB_BASE + 0x528)

/* GPIO Port E */
#define GPIO_PORTE_BASE           0x40024000
#define GPIO_PORTE_AFSEL_R        HWREG(GPIO_PORTE_BASE + 0x420)
#define GPIO_PORTE_DEN_R          HWREG(GPIO_PORTE_BASE + 0x51C)
#define GPIO_PORTE_AMSEL_R        HWREG(GPIO_PORTE_BASE + 0x528)

/* PWM0 */
#define PWM0_BASE                 0x40028000
#define PWM0_CTL_R                HWREG(PWM0_BASE + 0x000)
#define PWM0_ENABLE_R             HWREG(PWM0_BASE + 0x008)
#define PWM0_0_CTL_R              HWREG(PWM0_BASE + 0x040)
#define PWM0_0_GENA_R             HWREG(PWM0_BASE + 0x060)
#define PWM0_0_LOAD_R             HWREG(PWM0_BASE + 0x050)
#define PWM0_0_CMPA_R             HWREG(PWM0_BASE + 0x058)

/* ADC0 */
#define ADC0_BASE                 0x40038000
#define ADC0_ACTSS_R              HWREG(ADC0_BASE + 0x000)
#define ADC0_EMUX_R               HWREG(ADC0_BASE + 0x014)
#define ADC0_SSPRI_R              HWREG(ADC0_BASE + 0x020)
#define ADC0_SSMUX3_R             HWREG(ADC0_BASE + 0x0A0)
#define ADC0_SSCTL3_R             HWREG(ADC0_BASE + 0x0A4)
#define ADC0_PSSI_R               HWREG(ADC0_BASE + 0x028)
#define ADC0_RIS_R                HWREG(ADC0_BASE + 0x004)
#define ADC0_ISC_R                HWREG(ADC0_BASE + 0x00C)
#define ADC0_SSFIFO3_R            HWREG(ADC0_BASE + 0x0A8)
#define ADC0_IM_R                 HWREG(ADC0_BASE + 0x008)
#define ADC0_CTL_R                HWREG(ADC0_BASE + 0x038)
#define ADC0_PC_R                 HWREG(ADC0_BASE + 0xFC4)

#define ADC_SSPRI_SS3_0           0x00000003

#define ADC_SSCTL3_END            0x00000002
#define ADC_SSCTL3_IE             0x00000004

/* Timer0 */
#define TIMER0_BASE               0x40030000
#define TIMER0_CTL_R              HWREG(TIMER0_BASE + 0x00C)
#define TIMER0_CFG_R              HWREG(TIMER0_BASE + 0x000)
#define TIMER0_TAMR_R             HWREG(TIMER0_BASE + 0x004)
#define TIMER0_TAILR_R            HWREG(TIMER0_BASE + 0x028)
#define TIMER0_ICR_R              HWREG(TIMER0_BASE + 0x024)
#define TIMER0_IMR_R              HWREG(TIMER0_BASE + 0x018)

#define TIMER_TAMR_TAMR_PERIOD    0x00000002
#define TIMER_TAMR_TACDIR         0x00000010
#define TIMER_CTL_TAEN            0x00000001
#define TIMER_IMR_TATOIM          0x00000001
#define TIMER_ICR_TATOCINT        0x00000001

/* NVIC */
#define NVIC_EN0_R                HWREG(0xE000E100)
#define NVIC_PRI4_R               HWREG(0xE000E410)

#define NVIC_EN0_TIMER0A          (1u << 19)
#define NVIC_PRI4_TIMER0A_M       0xE0000000
#define NVIC_PRI4_TIMER0A_S       29

/* Cortex-M peripherals */
#define NVIC_SYS_CTRL             HWREG(0xE000ED10)
#define NVIC_SYS_CTRL_SEVONPEND   0x00000010

#endif /* TM4C123GH6PM_H_ */
