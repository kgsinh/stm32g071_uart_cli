#ifndef W25QXX_H_
#define W25QXX_H_

#include <stdint.h>

#include "spi.h"
#include "uart.h"
#include "systick.h"

typedef struct
{
	uint8_t manufacturer_id;
	uint8_t memory_type;
	uint8_t capacity;
} w25qxx_jedec_id_t;

void w25qxx_wake_up(void);
void w25qxx_reset(void);
w25qxx_jedec_id_t w25qxx_read_jedec_id(void);


#endif /* W25QXX_H_ */
