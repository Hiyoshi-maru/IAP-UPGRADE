#include "main.h"
#include "UART.h"
UART_HandleTypeDef UartHandle;
__IO ITStatus UartReady = RESET;
void Uart_init(void){
  UartHandle.Instance        = USARTx;
  UartHandle.Init.BaudRate   = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT; 
  if(HAL_UART_DeInit(&UartHandle)!=HAL_OK)Error_Handler();
  if(HAL_UART_Init(&UartHandle)!=HAL_OK)Error_Handler();
}
HAL_StatusTypeDef Uart_Transmit_IT(uint8_t *pData, uint16_t Size){
  uint32_t start=HAL_GetTick();
  if(HAL_UART_Transmit_IT(&UartHandle, pData, Size)!=HAL_OK){Uart_init();return HAL_ERROR;}
  while (UartReady != SET){
    if(HAL_GetTick()-start>=Timeout)break;
  }
  if(UartReady!=SET){Uart_init();return HAL_TIMEOUT;}
  else {UartReady = RESET;return HAL_OK;}
}
HAL_StatusTypeDef Uart_Receive_IT(uint8_t *pData, uint16_t Size){
  uint32_t start=HAL_GetTick();
  if(HAL_UART_Receive_IT(&UartHandle, pData, Size)!=HAL_OK){Uart_init();return HAL_ERROR;}
  while (UartReady != SET){
    if(HAL_GetTick()-start>=Timeout)break;
  }
  if(UartReady!=SET){Uart_init();return HAL_TIMEOUT;}
  else {UartReady = RESET;return HAL_OK;}
}
void disAstring(uint8_t* p){
  uint16_t length=0;
  while(p[length]!='\0')length++;
  Uart_Transmit_IT(p,length);
}
void sendByte(uint8_t data){
  Uart_Transmit_IT(&data,1);
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
    Error_Handler();
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  UartReady = SET;

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  UartReady = SET;
}