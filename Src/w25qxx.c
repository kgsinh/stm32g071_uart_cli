#include "w25qxx.h"


#define CMD_READ_JEDEC_ID       0x9F

void w25qxx_wake_up(void)
{
	static uint8_t wake_up_cmd = 0xABU;

	systickDelayus(4U);
	spi1_ss_enable();
	spi1_tx(&wake_up_cmd, 1U);
	spi1_ss_disable();

	systickDelayus(40U);
	printf("W25Qxx Wake Up Done\r\n");
}


void w25qxx_reset(void)
{
	uint8_t tdata[2] = {0x66, 0x99};

    // Send Reset Enable Command
    spi1_ss_enable();
    spi1_tx(&tdata[0], 1);
    spi1_ss_disable();

    systickDelayus(20); // 20μs to be safe

    //Send Reset Memory Command
    spi1_ss_enable();
    spi1_tx(&tdata[1], 1);
    spi1_ss_disable();

    // W25Q64 needs 30μs typical, 100μs max reset time
    systickDelayus(200); // 200μs to be safe

    printf("W25Q64 Reset Complete\r\n");
}

w25qxx_jedec_id_t w25qxx_read_jedec_id(void)
{
	uint8_t cmd = CMD_READ_JEDEC_ID;
	uint8_t response[3] = {0};
    w25qxx_jedec_id_t jedec_id = {0};

    spi1_ss_enable();

	/* Send Read JEDEC ID command */
    spi1_tx(&cmd, 1);

    /* Read 3 bytes of JEDEC ID */
    spi1_rx(response, 3);

    spi1_ss_disable();
    systickDelayus(5); // Small delay after operation

    jedec_id.manufacturer_id = response[0];
    jedec_id.memory_type = response[1];
    jedec_id.capacity = response[2];

    return jedec_id;
}

