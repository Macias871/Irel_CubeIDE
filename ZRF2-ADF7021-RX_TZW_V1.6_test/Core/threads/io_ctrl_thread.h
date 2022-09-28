/**
 * @file    io_ctrl_thread.hpp
 * @brief	IO control thread
 * @date    04-12-2012
 * @author	Adam Miotk
 */

#ifndef IO_CTRL_THREAD_HPP_
#define IO_CTRL_THREAD_HPP_

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"

#define KEY_CFG_STOP_ON	0x01
#define KEY_CFG_ANALOG 0x02
#define KEY_CFG_INVERT 0x04
#define KEY_CFG_OFF_RESET 0x80

extern xTaskHandle io_ctrl_task_handle;

void io_timer_callback(xTimerHandle timer_handle);

/**
 * @brief IO control thread
 * @param pvParameters
 */
void io_ctrl_task(void const * argument);

uint8_t spi_n(const uint8_t n, uint8_t t, uint8_t l, uint8_t *b);
uint8_t MAP_ANA(uint8_t EXT_type, uint8_t CH,  uint8_t Val_in, uint8_t ARR_num, uint8_t SRV);
uint8_t map(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max);
void pk_on(uint8_t pk);

void pk_off(uint8_t pk);


uint8_t frame_change_bit(
	uint8_t * const input_table,
	const uint8_t input_table_possiton,
	uint8_t * const frame,
	const uint8_t frame_bit_possition
);
#endif /* IO_CTRL_THREAD_HPP_ */
