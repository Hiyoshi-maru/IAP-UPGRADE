#ifndef __FLASH_OPERATION_H
#define __FLASH_OPERATION_H
/***********************头文件***********************/
#include "stm32f7xx_hal.h"
#include "main.h"
/****************************变量及常量定义************************************/
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* 扇区0基址, 32 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08008000) /* 扇区0基址, 32 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08010000) /* 扇区0基址, 32 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x08018000) /* 扇区0基址, 32 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08020000) /* 扇区0基址, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08040000) /* 扇区0基址, 256 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08080000) /* 扇区0基址, 256 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x080C0000) /* 扇区0基址, 256 Kbytes */
#define App_address             ((uint32_t)0x08010000)////////用户程序入口地址
#define App_End_adddress        ((uint32_t)0x0807FFFF)////////用户程序边界地址
#define Write_Startaddress      ((uint32_t)0x08080000)////////程序刷写地址
#define Write_Endaddress        ((uint32_t)0x080FFFFF)////////程序刷写结束地址
#define Flag_Start_address      ((uint32_t)0x08008000)////////标志区入口地址
#define Flag_End_address        ((uint32_t)0x0800FFFF)////////标志区边界地址
#define filelength_address      ((uint32_t)0x08008000)////////标志区文件长度地址
#define Upgrade_flag_address    ((uint32_t)0x08008004)////////标志区升级是否成功标志地址
typedef enum
{
  FLASH_Erase_OK =0,
  FLASH_Erase_ERROR,
  FLASH_Program_OK,
  FLASH_Program_ERROR
} FLASH_Status;
/*********************************函数声明*********************************************/
static uint32_t GetSector(uint32_t Address);
void Flash_config(void);
FLASH_Status Flash_Erase(uint32_t Address1,uint32_t Address2);
void Program_Cpy(void);
#endif