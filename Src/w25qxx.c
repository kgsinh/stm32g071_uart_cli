#include "w25qxx.h"
#include "spi.h"
#include "uart.h"

#define CMD_READ_JEDEC_ID       0x9F

w25qxx_jedec_id_t w25qxx_read_jedec_id(void)
{
	w25qxx_jedec_id_t jedec_id = {0};

	uint8_t cmd = CMD_READ_JEDEC_ID;
	uint8_t id_data[3] = {0};

	spi1_ss_enable();
	spi1_tx(&cmd, 1);
	spi1_rx(id_data, 3);
	spi1_ss_disable();

	jedec_id.manufacturer_id = id_data[0];
	jedec_id.memory_type = id_data[1];
	jedec_id.capacity = id_data[2];

	return jedec_id;
}
