#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include"stm32g071xx.h"
#include "uart.h"
#include "systick.h"
#include "led.h"
#include "cli.h"
#include "spi.h"
#include "w25qxx.h"

int main(void)
{
    memset(command, 0, CMD_SIZE);

    UARTinit();
    led_init();

    // Initialize SPI
    spi1_gpio_init();
    spi1_config(); // Now running at 250kHz

    // W25Q64 power-up sequence (needs 10ms typical)
    printf("W25Q64 Power-up delay...\r\n");
    systickDelayus(15000); // 15ms power-up time

    // Hardware reset sequence
    w25qxx_reset();

    green_led_off();
    blue_led_off();

    printf("UART CLI Ready. Type 'help' for commands.\r\n");

    while (1)
    {
        if (UART_read_cmd())
        {
            printf("Received command: %s\n\r", command);
            process_command(command);
            memset(command, 0, CMD_SIZE);
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
