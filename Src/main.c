#include "uart.h"
#include "systick.h"
#include "led.h"

int main(void)
{
	memset(command, 0, CMD_SIZE);

	UARTinit();
	led_init();

	green_led_off();
	blue_led_off();

	printf("UART CLI Application\n\r");

	while (1) {
		if (UART_read_cmd())
		{
			printf("Received command: %s\n\r", command);

			if (strncmp((const char*) command, "led on", 6) == 0)
			{
				green_led_on();
				systickDelayms(500);
				printf("LED is ON\n\r");
			}

			else if (strncmp((const char*) command, "led off", 7) == 0)
			{
				green_led_off();
				systickDelayms(500);
				printf("LED is OFF\n\r");
			} else
			{
				printf("Invalid command. Please use 'led on' or 'led off'.\n\r");
			}
		}
	}

	return 0;
}

void USART2_IRQHandler(void)
{
	if (USART2->ISR & (1 << 5))
	{ //RXNE is set
		uint8_t rx_data = (uint8_t) USART2->RDR;

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
