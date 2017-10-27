#ifndef __IAP_H
#define __IAP_H
#include "Flash_operation.h"
#include "stm32f7xx_hal_cortex.h"
#define Upgrade_OK           (uint32_t)0x00000000
#define Upgrade_Fail         (uint32_t)0x10101010
void IAP(void);
#endif