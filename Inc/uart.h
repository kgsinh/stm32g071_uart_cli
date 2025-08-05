/**
 * @file uart.h
 * @brief This header file has functions to initialize UART and to transmit
 * data
 *
 */

#ifndef UART_H_
#define UART_H_

#include"stm32g071xx.h"

#include<stdint.h>
#include<stdio.h>

/**
 * @fn void USARTinit(void)
 * @brief This function will initialize the UART2 peripheral
 *
 */
void USARTinit(void);

/**
 * @fn void USART_TX_STR(char*)
 * @brief This function will transmit the data
 *
 * @param str
 */
void USART_TX_STR(char *str);


#endif /* UART_H_ */
