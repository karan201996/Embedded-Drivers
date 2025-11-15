#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>

void SystemInit(void);
void SystemClock_Config(void);
void System_EnableModuleClocks(void);
uint32_t SystemCoreClockGet(void);

#endif /* SYSTEM_H_ */
