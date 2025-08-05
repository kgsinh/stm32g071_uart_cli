#include "uart.h"
#include "systick.h"
#include "led.h"

int main(void)
{
	USARTinit();
	led_init();
	green_led_off();
	blue_led_off();
	while(1)
	{
		printf("Green LED ON...\n\r");
		green_led_on();
		systickDelayms(1000);
		printf("Green LED OFF...\n\r");
		green_led_off();
		systickDelayms(1000);

	}

	return 0;
}
