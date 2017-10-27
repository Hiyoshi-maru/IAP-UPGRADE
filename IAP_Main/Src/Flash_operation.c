#include "Flash_operation.h"
static FLASH_EraseInitTypeDef EraseInitStruct;

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
FLASH_Status FLASH_Write_8(uint32_t FlashAddress, uint8_t* Data ,uint32_t DataLength)
{
  uint32_t i = 0;

  for (i = 0; (i < DataLength) && (FlashAddress <= (Write_Endaddress)); i++)
  {
    if (HAL_FLASH_Program(TYPEPROGRAM_BYTE, FlashAddress, *(uint8_t*)(Data+i)) == HAL_OK)      
    {
      if (*(uint8_t*)FlashAddress != *(uint8_t*)(Data+i))
      {
        return(FLASH_Program_ERROR);
      }
      FlashAddress += 1;
    }
    else
    {
      return (FLASH_Program_ERROR);
    }
  }

  return (FLASH_Program_OK);
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