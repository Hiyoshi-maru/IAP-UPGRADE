#ifndef __FLASH_OPERATION_H
#define __FLASH_OPERATION_H
/***********************ͷ�ļ�***********************/
#include "stm32f7xx_hal.h"
/****************************��������������************************************/
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* ����0��ַ, 32 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08008000) /* ����0��ַ, 32 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08010000) /* ����0��ַ, 32 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x08018000) /* ����0��ַ, 32 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08020000) /* ����0��ַ, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08040000) /* ����0��ַ, 256 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08080000) /* ����0��ַ, 256 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x080C0000) /* ����0��ַ, 256 Kbytes */
#define BOOT_start_address      ((uint32_t)0x08000000)
#define BOOT_End_address        ((uint32_t)0x08007FFF)
#define App_address             ((uint32_t)0x08010000)////////�û�������ڵ�ַ
#define App_End_adddress        ((uint32_t)0x0807FFFF)////////�û�����߽��ַ
#define Write_Startaddress      ((uint32_t)0x08080000)////////����ˢд��ַ
#define Write_Endaddress        ((uint32_t)0x080FFFFF)////////����ˢд������ַ
#define Flag_Start_address      ((uint32_t)0x08008000)////////��־����ڵ�ַ
#define Flag_End_address        ((uint32_t)0x0800FFFF)////////��־���߽��ַ
#define filelength_address      ((uint32_t)0x08008000)////////��־���ļ����ȵ�ַ
#define Upgrade_flag_address    ((uint32_t)0x08008004)////////��־�������Ƿ�ɹ���־��ַ
typedef enum
{
  FLASH_Erase_OK =0,
  FLASH_Erase_ERROR,
  FLASH_Program_OK,
  FLASH_Program_ERROR
} FLASH_Status;
/*********************************��������*********************************************/
static uint32_t GetSector(uint32_t Address);
void Flash_config(void);
FLASH_Status Flash_Erase(uint32_t Address1,uint32_t Address2);
FLASH_Status FLASH_Write_8(uint32_t FlashAddress, uint8_t* Data ,uint32_t DataLength);
#endif