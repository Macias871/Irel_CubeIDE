
#ifndef IO_CTRL_THREAD_HPP_
#define IO_CTRL_THREAD_HPP_

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"




//#define NULL_INPUT 0xff;
//#define PIN_OUTPUT 0xFE;

void ext_task(void const * argument);

uint8_t spi_n(uint8_t n, uint8_t t, uint8_t l, uint8_t *b);

void read_main_sws(void);

extern xTaskHandle io_ctrl_task_handle;

/**
 * @brief IO control thread
 * @param pvParameters
 */
void io_ctrl_task(void const * argument);

uint8_t frame_change_bit(
	uint8_t * const input_table,
	const uint8_t input_table_possiton,
	uint8_t * const frame,
	const uint8_t frame_bit_possition
);
#endif /* IO_CTRL_THREAD_HPP_ */
