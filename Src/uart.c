#include "uart.h"


uint8_t command[CMD_SIZE];
static void UART_TX(char data);

/*Retargeted printf*/
int __io_putchar(char data) {
	UART_TX(data);
	return data;
}

void UARTinit(void) {
	// 1 start bit, 8 Data bits, 1 Stop bit, Even Parity
	RCC->APBENR1 |= (1 << 17); //Enable USART2 clock
	RCC->IOPENR |= (1 << 0);  //Enable GPIOA clock
	GPIOA->MODER &= ~(3 << 4); //00
	GPIOA->MODER |= (2 << 4); //PA2(10) AS ALTERNATE FNC
	GPIOA->AFR[0] |= (1 << 8); // AF1 for PA2 AS UART TX
	USART2->BRR = 0x341; //BAUDRATE 19200
	USART2->CR1 |= (1 << 3); //TRANSMIT ENABLE
	GPIOA->MODER &= ~(3 << 6); //00
	GPIOA->MODER |= (2 << 6); //PA3(10) AS ALTERNATE FNC
	GPIOA->AFR[0] |= (1 << 12); // AF1 for PA3 AS UART RX
	USART2->CR1 |= (1 << 2); //RECEIVE ENABLED
	USART2->CR1 |= (1 << 0); //USART ENABLED
	//NVIC->ISER[0] |= (1<<28); //POSITION 28

}

uint8_t UART_RX(void) {
	/**Wait until RXNE is set**/
	while (!((USART2->ISR) & (1 << 5)))
		;
	return (uint8_t) (USART2->RDR);
}

static void UART_TX(char data) {
	while (!((USART2->ISR) & (1 << 6)))
		;
	USART2->TDR = data;
}

bool UART_read_cmd(void) {
	static uint8_t index = 0;
	uint8_t rx_data = UART_RX();

	if (rx_data == '\r' || rx_data == '\n') {
		command[index] = '\0'; //Null terminate the command
		index = 0; //Reset index for next command
		return true; //Command is ready
	} else {
		if (index < CMD_SIZE - 1) { //Leave space for null terminator
			command[index++] = rx_data;
		}
		return false; //Command not complete yet
	}
}


