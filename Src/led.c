#include "led.h"

void led_init() {
	/*Enable GPIOB clock*/
	RCC->IOPENR |= (1U << 1);

	/*PB4 as an output*/
	GPIOB->MODER |= 1U << 8; //PB4
	GPIOB->MODER &= ~(1U << 9); //O/P

	/*make PB4 high speed*/
	GPIOB->OSPEEDR |= (2U << 8);

	/*PB14 as an output*/
	GPIOB->MODER |= 1U << 28; //PB14
	GPIOB->MODER &= ~(1U << 29); // O/P

	/*make PB14 high speed*/
	GPIOB->OSPEEDR |= (2U << 28);

}

void green_led_on() {
	/*Set PB4*/
	GPIOB->BSRR |= 1U << 4;
}

void green_led_off() {
	/*Reset PB4*/
	GPIOB->BSRR |= (1U << 20);
}

void blue_led_on() {
	/*Set PB14*/
	GPIOB->BSRR |= (1U << 14);
}

void blue_led_off() {
	/*Reset PB14*/
	GPIOB->BSRR |= (1U << 30);
}
