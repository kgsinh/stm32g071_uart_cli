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
#include<stdbool.h>

#define CMD_SIZE 64

extern uint8_t command[CMD_SIZE];


/**
 * @fn void UARTinit(void)
 * @brief This function will initialize the UART2 peripheral
 *
 */
void UARTinit(void);

/**
 * @fn uint8_t UART_RX(void)
 * @brief This function will receive the data
 *
 * @return uint8_t
 */
uint8_t UART_RX(void);


/**
 * @fn void UART_TX_STR(char*)
 * @brief This function will transmit the data
 *
 * @param str
 */
void UART_TX_STR(char *str);

bool UART_read_cmd(void);



#endif /* UART_H_ */
