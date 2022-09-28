/**
 * @file    cmd_thread.hpp
 * @brief	Command terminal control thread
 * @date    05-01-2013
 * @author	Adam Miotk
 */

#ifndef CMD_THREAD_HPP_
#define CMD_THREAD_HPP_


void cfg_write_to_flash(const uint8_t * const buffer, const uint16_t size);

//xTaskHandle cmd_task_handle;

/**
 * @brief CMD thread
 * @param pvParameters
 */
void cmd_task(void const * argument);

/**
 * @brief Execute user command
 * @param cmd - user command
 */
void cmd_execute(char * cmd);

/**
 * @brief Write single byte to buffer
 * @param buffer - pointer to the buffer
 * @param byte - byte to be write to the buffer
 * @param counter - position of last byte in the buffer
 * @param cfg_length - length of configuration file
 */
uint8_t usr_cfg_write_to_buffer(
	uint8_t * const buffer,
	const uint8_t byte,
	uint16_t * const counter,
	const uint16_t cfg_length
);



void JumpToBootloader(void);




void serial_send_string(char *str);
void serial_send_string_len(char *str, uint32_t len);

/**
 * @brief Exchange spaces for zeros in string
 * @param str - string parameter
 */
void string_zero_fill(char *str);

void usart1Putc(uint8_t p);
uint8_t uint_to_ascii(
	uint8_t const uint,
	uint8_t * const ascii_high,
	uint8_t * const ascii_low
);
uint8_t ascii_to_uint(
	uint8_t const ascii_high,
	uint8_t const ascii_low,
	uint8_t * const uint
);
#define TRANSFER_FS_NO_ERRORS		0U

uint8_t return_ASCII(
	uint8_t num
);

uint8_t return_uint(
	uint8_t ascii
);

#endif /* CMD_THREAD_HPP_ */
