#ifndef __MAIN_H
#define __MAIN_H
#include "Flash_operation.h"
#include "UART.h"
#include "Com.h"
#include "stm32f7xx_hal_iwdg.h"
static void SystemClock_Config(void);
void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
void Usercode(void);
void Deinit(void);
#endif