#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include"stm32g071xx.h"
#include "uart.h"
#include "systick.h"
#include "led.h"
#include "cli.h"
#include "spi.h"

int main(void)
{
	memset(command, 0, CMD_SIZE);

	UARTinit();
	led_init();
	spi1_gpio_init();
	spi1_config();

	green_led_off();
	blue_led_off();

	printf("UART CLI Application\n\r");

	while (1)
	{
		if (UART_read_cmd())
		{
			printf("Received command: %s\n\r", command);
			process_command(command);
			memset(command, 0, CMD_SIZE); // Clear command buffer
		}
	}

	return 0;
}

void USART2_IRQHandler(void)
{
	if (USART2->ISR & (1 << 5))
	{ //RXNE is set
		char rx_data = USART2->RDR;

		static uint8_t index = 0;

		if (rx_data == '\r' || rx_data == '\n')
		{
			command[index] = '\0';  // Null terminate

			index = 0;
			command_ready = true;   // Signal main loop
		}
		else
		{
			if (index < CMD_SIZE - 1)
			{
				command[index++] = rx_data;
			}
		}
	}
}
