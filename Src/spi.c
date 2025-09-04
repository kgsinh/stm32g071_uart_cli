#include "spi.h"

#define SPI1EN  (1U << 12)
#define GPIOAEN (1U << 0)

//PA5 - SCK
//PA6 - MISO
//PA7 - MOSI
//PA9 - SS


void spi1_gpio_init(void)
{
	RCC->IOPENR |= GPIOAEN; //Enable GPIOA clock

	/*Set PA5, PA6, PA7 mode to alternate function*/

	/*PA5*/
	GPIOA->MODER &= ~(3U << 10); //Clear
	GPIOA->MODER |= (2U << 10); //Set to alternate function
	GPIOA->AFR[0] |= (0U << 20); //Set to AF0

	/*PA6*/
	GPIOA->MODER &= ~(3U << 12); //Clear
	GPIOA->MODER |= (2U << 12); //Set to alternate function
	GPIOA->AFR[0] |= (0U << 24); //Set to AF0

	/*PA7*/
	GPIOA->MODER &= ~(3U << 14); //Clear
	GPIOA->MODER |= (2U << 14); //Set to alternate function
	GPIOA->AFR[0] |= (0U << 28); //Set to AF0

	/*PA9*/
	GPIOA->MODER &= ~(3U << 18); //Clear
	GPIOA->MODER |= (1U << 18); //Set to general purpose output mode
	GPIOA->MODER &= ~(1U << 19); //Set to general purpose output mode
}

void spi1_config(void)
{
	/*Enable SPI1 peripheral clock*/
	RCC->APBENR2 |= SPI1EN;

	/*set clock to fpclk/4*/
	SPI1->CR1 |= (1U << 3); //BR0
	SPI1->CR1 &= ~(1U << 4); //BR1
	SPI1->CR1 &= ~(1U << 5); //BR2

	/*set CPOL to 1 & CPHA to 1*/
	SPI1->CR1 |= (1U << 0); //CPHA
	SPI1->CR1 |= (1U << 1); //CPOL

	/*set to full duplex mode*/
	SPI1->CR1 &= ~(1U << 10); //RXONLY

	/*set MSB first*/
	SPI1->CR1 &= ~(1U << 7); //LSBFIRST

	/*set to master mode*/
	SPI1->CR1 |= (1U << 2); //MSTR

	/*set to 8 bit data frame format*/
	SPI1->CR2 &= ~(1U << 8); //DS0
	SPI1->CR2 |= (1U << 9); //DS1
	SPI1->CR2 |= (1U << 10); //DS2
	SPI1->CR2 |= (1U << 11); //DS3

	/*Enable software slave management and set SSI*/
	SPI1->CR1 |= (1U << 9); //SSM
	SPI1->CR1 |= (1U << 8); //SSI

	/*Enable SPI1*/
	SPI1->CR1 |= (1U << 6); //SPE
}


