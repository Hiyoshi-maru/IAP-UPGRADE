#include "main.h"
__IO uint32_t UserButtonStatus = 0;
extern UART_HandleTypeDef UartHandle;
typedef void(*function_pointer)(void);
function_pointer ADDRESS;
uint32_t temp_address;
int main(void)
{
  SCB->VTOR=0x08000000|0x10000;///此句不可删除
  uint8_t state;
  MPU_Config();
  CPU_CACHE_Enable();
  HAL_Init();
  SystemClock_Config();
  Uart_init();
  BSP_LED_Init(LED1);
  BSP_LED_On(LED1);
  while(1){
    state=Communication();
    if(state==1){
      Deinit();
      __set_FAULTMASK(1);
      HAL_NVIC_SystemReset();
      
    }
    else Usercode();
  }
  
}
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}
void Error_Handler(void)//出现错误，LED1 1S闪烁
{
  BSP_LED_On(LED1);
  while(1)
  {
    BSP_LED_Toggle(LED1);
    HAL_Delay(1000);
  }
}
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;  
  HAL_MPU_Disable();
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
static void CPU_CACHE_Enable(void)
{
  SCB_EnableICache();
  SCB_EnableDCache();
}
void Usercode(void){
  BSP_LED_Toggle(LED1);
  //HAL_Delay(100);
}
void Deinit(void){
    HAL_UART_DeInit(&UartHandle);
    BSP_PB_DeInit(BUTTON_KEY);
    BSP_LED_DeInit(LED1);
    HAL_DeInit();
}


