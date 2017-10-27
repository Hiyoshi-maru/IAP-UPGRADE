#ifndef __UART_H
#define __UART_H
/***********************ͷ�ļ�***********************/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal.h"
#include "stm32746g_discovery.h"
/***********************��������������***********************/
#define USARTx                           USART1
#define USARTx_CLK_ENABLE()              __USART1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __USART1_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __USART1_RELEASE_RESET()

/* USARTx���Ŷ��� */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART1
#define USARTx_RX_PIN                    GPIO_PIN_7
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF7_USART1

/* USARTxz�ж����� */
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler

#define Timeout  1000
/***************************��������*********************************/
void Uart_init(void);
HAL_StatusTypeDef Uart_Transmit_IT(uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef Uart_Receive_IT(uint8_t *pData, uint16_t Size);
void sendByte(uint8_t data);
#endif