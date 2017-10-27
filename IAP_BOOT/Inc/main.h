#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f7xx_hal.h"
#include "Flash_operation.h"
#include "stm32746g_discovery.h"
#include "IAP.h"
static void SystemClock_Config(void);
void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
#endif