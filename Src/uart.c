#include "uart.h"

static void USART_TX(char data);

/*Retargeted printf*/
int __io_putchar(char data)
{
	USART_TX(data);
	return data;
}

void USARTinit(void){
	// 1 start bit, 8 Data bits, 1 Stop bit, Even Parity
	RCC->APBENR1 |= (1<<17); //Enable USART2 clock
	RCC->IOPENR |= (1<<0);  //Enable GPIOA clock
	GPIOA->MODER &= ~(3<<4); //00
	GPIOA->MODER |= (2<<4); //PA2(10) AS ALTERNATE FNC
	GPIOA->AFR[0] |= (1<<8); // AF1 for PA2 AS UART TX
	USART2->BRR = 0x341; //BAUDRATE 19200
	USART2->CR1 |= (1<<3); //TRANSMIT ENABLE
	GPIOA->MODER &= ~(3<<6); //00
	GPIOA->MODER |= (2<<6); //PA3(10) AS ALTERNATE FNC
	GPIOA->AFR[0] |= (1<<12); // AF1 for PA3 AS UART RX
	USART2->CR1 |= (1<<2); //RECEIVE ENABLED
	USART2->CR1 |= (1<<0) ; //USART ENABLED
	//NVIC->ISER[0] |= (1<<28); //POSITION 28

}

static void USART_TX(char data)
{
	while(!((USART2->ISR)&(1<<6)));
	USART2->TDR = data;
}
