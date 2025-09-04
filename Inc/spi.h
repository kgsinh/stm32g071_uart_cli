#ifndef SPI_H_
#define SPI_H_

#include "stm32g071xx.h"

#include <stdint.h>

void spi1_gpio_init(void);
void spi1_config(void);
void spi1_tx(uint8_t *data, uint32_t size);
void spi1_rx(uint8_t *data, uint32_t size);
void spi1_ss_enable(void);
void spi1_ss_disable(void);


#endif /* SPI_H_ */
