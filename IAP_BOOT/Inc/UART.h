#ifndef __UART_H
#define __UART_H
/***********************头文件***********************/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
/***********************变量及常量定义***********************/
#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __USART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART1_RELEASE_RESET()

/* USARTx引脚定义 */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF7_USART1

/* USARTxz中断设置 */
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler

#define Timeout  5000
/***************************函数声明*********************************/
void Uart_init(void);
HAL_StatusTypeDef Uart_Transmit_IT(uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef Uart_Receive_IT(uint8_t *pData, uint16_t Size);
void disAstring(uint8_t* p);
void sendByte(uint8_t data);
#endif