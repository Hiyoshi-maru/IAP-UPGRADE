#include "IAP.h"
#include "main.h"
typedef void(*function_pointer)(void);
function_pointer ADDRESS;
uint32_t temp_address;
uint32_t Upgrade_flag;
uint32_t filelength;
extern UART_HandleTypeDef UartHandle;
void IAP(void){
  Upgrade_flag=*(__IO uint32_t*)(Upgrade_flag_address);
  filelength=*(__IO uint32_t*)(filelength_address);
  if(Upgrade_flag==Upgrade_OK){
      Flash_Erase(App_address,App_End_adddress);
      Program_Cpy();
      Flash_Erase(Flag_Start_address,Flag_End_address);////清除程序标志区
  }
  if (((*(__IO uint32_t*)App_address) & 0x2FFE0000 ) == 0x20000000){
        temp_address = *(__IO uint32_t*) (App_address+ 4);
        ADDRESS=(function_pointer)temp_address;
        __set_MSP((*(__IO uint32_t*) App_address));
        ADDRESS();
   }
}