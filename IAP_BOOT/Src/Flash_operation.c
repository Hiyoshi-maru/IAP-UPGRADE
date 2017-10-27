#include "Flash_operation.h"
static FLASH_EraseInitTypeDef EraseInitStruct;
extern uint32_t filelength;
/**************************有关Flash操作的一切函数*************************************/
void Flash_config(void){
  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                         FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_ERSERR);//清除一切标志位
}
FLASH_Status Flash_Erase(uint32_t Address1,uint32_t Address2){
  uint32_t SectorError;
  uint32_t FirstSector,NbofSectors;
  Flash_config();
  FirstSector = GetSector(Address1);
  NbofSectors = GetSector(Address2) - FirstSector + 1;
  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;
  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
  EraseInitStruct.Sector        = FirstSector;
  EraseInitStruct.NbSectors     = NbofSectors;
   if (HAL_FLASHEx_Erase(&EraseInitStruct, &SectorError) != HAL_OK)
  {
     return (FLASH_Erase_ERROR);
  }
  
  return (FLASH_Erase_OK);
  
}
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;
  }
  else /* (Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_7) */
  {
    sector = FLASH_SECTOR_7;
  }
  return sector;
}
void Program_Cpy(void){
  uint32_t Address1,Address2;
  Address2=App_address;
  for(Address1=Write_Startaddress;(Address1<Write_Startaddress+filelength)&&Address1<=(Write_Endaddress)&&Address2<=(App_End_adddress);Address1++){
    if(HAL_FLASH_Program(TYPEPROGRAM_BYTE,Address2,*(uint8_t*)Address1)!=HAL_OK){Error_Handler();}
    Address2++;
  }
}