#include "spi.h"

#define SPI1EN  (1U << 12)
#define GPIOAEN (1U << 0)
#define SR_TXE  (1U << 1)
#define SR_BSY  (1U << 7)

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
	GPIOA->OSPEEDR |= (3U << 10); //Set to high speed
	GPIOA->AFR[0] &= ~(0xFU << 20); //Clear
	GPIOA->AFR[0] |= (0U << 20); //Set to AF0

	/*PA6*/
	GPIOA->MODER &= ~(3U << 12); //Clear
	GPIOA->MODER |= (2U << 12); //Set to alternate function
	GPIOA->OSPEEDR |= (3U << 12); //Set to high speed
	GPIOA->AFR[0] &= ~(0xFU << 24); //Clear
	GPIOA->AFR[0] |= (0U << 24); //Set to AF0

	/*PA7*/
	GPIOA->MODER &= ~(3U << 14); //Clear
	GPIOA->MODER |= (2U << 14); //Set to alternate function
	GPIOA->OSPEEDR |= (3U << 14); //Set to high speed
	GPIOA->AFR[0] &= ~(0xFU << 28); //Clear
	GPIOA->AFR[0] |= (0U << 28); //Set to AF0

	/*PA9*/
	GPIOA->MODER &= ~(3U << 18); //Clear
	GPIOA->MODER |= (1U << 18); //Set to general purpose output mode
	GPIOA->OSPEEDR |= (3U << 18); //Set to high speed
	GPIOA->OTYPER &= ~(1U << 9); //Set to push pull
	GPIOA->PUPDR &= ~(3U << 18); //No pull up pull down

	GPIOA->BSRR = (1U << 9); //SS HIGH
}

void spi1_config(void)
{
	/*Enable SPI1 peripheral clock*/
	RCC->APBENR2 |= SPI1EN;

	/*Disable SPI1 before configuration*/
	SPI1->CR1 &= ~(1U << 6); //SPE

	/*set clock to fpclk/2*/
	SPI1->CR1 &= ~(1U << 3); //BR0
	SPI1->CR1 &= ~(1U << 4); //BR1
	SPI1->CR1 &= ~(1U << 5); //BR2

	/*set CPOL to 0 & CPHA to 0*/
	SPI1->CR1 &= ~(1U << 0); //CPHA
	SPI1->CR1 &= ~(1U << 1); //CPOL

	/*set to full duplex mode*/
	SPI1->CR1 &= ~(1U << 10); //RXONLY

	/*set MSB first*/
	SPI1->CR1 &= ~(1U << 7); //LSBFIRST

	/*set to master mode*/
	SPI1->CR1 |= (1U << 2); //MSTR

	/*set to 8 bit data frame format*/
	SPI1->CR2 &= ~(0xF << 8); //clear DS
	SPI1->CR2 |= (1U << 8); //DS0
	SPI1->CR2 |= (1U << 9); //DS1
	SPI1->CR2 |= (1U << 10); //DS2
	SPI1->CR2 &= ~(1U << 11); //DS3

	SPI1->CR2 |= (1U << 12); //FRXTH

	/*Disable NSS Output for software management*/
	SPI1->CR2 &= ~(1U << 2); //SSOE

	/*Enable software slave management and set SSI*/
	SPI1->CR1 |= (1U << 9); //SSM
	SPI1->CR1 |= (1U << 8); //SSI

	/*Enable SPI1*/
	SPI1->CR1 |= (1U << 6); //SPE
}

void spi1_tx(uint8_t *data, uint32_t size)
{
	uint32_t i=0U;

	if ((data == NULL) || (size == 0U))
	{
		return;
	}

	while (i < size)
	{
		/*Wait until TXE is set*/
		while (!(SPI1->SR & SR_TXE));

		/*8-bit write to DR*/
		*(volatile uint8_t *)&SPI1->DR = data[i];
		i++;
	}

	/*Wait until TXE is set*/
	while (!(SPI1->SR & SR_TXE));

	while (SPI1->SR & SR_BSY); // wait not busy

	/*Clear OVR flag*/
	(void)SPI1->DR;
	(void)SPI1->SR;
}

void spi1_rx(uint8_t *data, uint32_t size)
{
	if ((data == NULL) || (size == 0U))
	{
		return;
	}

	while (size)
	{
		SPI1->DR = 0xFF; //send dummy byte

		/*Wait until TXE is set*/
		while (!(SPI1->SR & SR_TXE));

		/*Wait until RXNE is set*/
		while (!(SPI1->SR & (1U << 0)));

		/*Read data from register*/
		*data = SPI1->DR;
		data++;
		size--;
	}
}

void spi1_ss_enable(void)
{
	GPIOA->BSRR = (1U << (9 + 16)); //SS LOW
}

void spi1_ss_disable(void)
{
	GPIOA->BSRR = (1U << 9); //SS HIGH
}

