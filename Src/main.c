#include "uart.h"
#include "systick.h"
#include "led.h"

int main(void) {
	UARTinit();
	led_init();
	green_led_off();
	blue_led_off();
	printf("UART CLI Application\n\r");

	while (1) {
		if (UART_read_cmd())
		{
		printf("Received command: %s\n\r", command);

		if (strncmp((const char*)command, "led on", 6) == 0)
		{
			green_led_on();
			systickDelayms(500);
			printf("LED is ON\n\r");
		}

		else if (strncmp((const char*)command, "led off", 7) == 0)
		{
			green_led_off();
			systickDelayms(500);
			printf("LED is OFF\n\r");
		}
		else
		{
			printf("Invalid command. Please use 'led on' or 'led off'.\n\r");
		}
		}
	}

	return 0;
}
