/**
 * @file    ctrl_thread.hpp
 * @brief	System control thread
 * @date    17-12-2012
 * @author	Adam Miotk
 */

#ifndef CTRL_THREAD_HPP_
#define CTRL_THREAD_HPP_

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"

extern xTaskHandle ctrl_task_handle;

/**
 * @brief System control thread
 * @param pvParameters
 */
void ctrl_task(void const * argument);

/**
 * @brief Display error code on led
 * @param code - code to be displayed
 * @param led_port - led connection port
 * @param led_pin - led connection pin
 * @param blink_interval - time between blink
 * @param digit_interval - time between digits
 * @param time_offset - time after code
 */
void blink_error_code(
	uint8_t code,
	GPIO_TypeDef * led_port,
	uint32_t led_pin,
	uint16_t blink_interval,
	uint16_t digit_interval,
	uint16_t time_offset
);

#endif /* CTRL_THREAD_HPP_ */
