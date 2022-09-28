/**
 * @file    ctrl_thread.cpp
 * @brief	System control thread
 * @date    17-12-2012
 * @author	Adam Miotk
 */

#include <stdint.h>
#include "../threads/ctrl_thread.h"

#include "variables.h"


#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"
//extern IWDG_HandleTypeDef hiwdg;

xTaskHandle usr_ctrl_task_handle;

void ctrl_task(void const * argument) {
vTaskDelay(100/portTICK_RATE_MS);


	if (1 == check_crc_eeprom()) {
	system_errors.cfg_crc = 1;}
	else{system_errors.cfg_crc = 0;}

while(system_errors.cfg_crc == 1)
{

	vTaskDelay(100/portTICK_RATE_MS);
	blink_error_code(40, LEDR_GPIO_Port, LEDR_Pin, 100U, 100U, 150U);

}

	  for(;;)
	  {


			if (rx_cfg.cfg_ver != CFG_VERSION) {
				system_errors.cfg_ver = 1;
			}

			if (rx_cfg.fb_len == 0xFFFF) {
				system_errors.cfg_len = 1;
			}

if(programmode == 0)
{


			if (system_errors.spi_disc == 1) {
				blink_error_code(11, LEDR_GPIO_Port, LEDR_Pin, 40U, 10U, 60U);
			}
			else
			{

			if (system_errors.cfg_ver == 1) {
				blink_error_code(12, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.cfg_len == 1) {
				blink_error_code(13, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.cfg_crc == 1) {
				blink_error_code(14, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.invalid_cfg == 1) {
				blink_error_code(15, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.main_ctrl == 1) {
				blink_error_code(23, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.pks_ctrl == 1) {
				blink_error_code(24, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.supply_short == 1) {
				blink_error_code(25, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}
			if (system_errors.supply_err == 1) {
				blink_error_code(26, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}

			if (system_errors.spi_ext == 1) {
				blink_error_code(31, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 1000U);
			}

			}
}
			while(programmode == 1)
			  {
				vTaskDelay(10/portTICK_RATE_MS);
				blink_error_code(11, LEDR_GPIO_Port, LEDR_Pin, 80U, 40U, 100U);

			  }
			vTaskDelay(10/portTICK_RATE_MS);
	}
}

void blink_error_code(
	uint8_t code,
	GPIO_TypeDef * led_port,
	uint32_t led_pin,
	uint16_t blink_interval,
	uint16_t digit_interval,
	uint16_t time_offset
) {
	uint8_t loop_counter = 0;
	uint8_t code_high_digit = code / 10U;
	uint8_t code_low_digit = code % 10;

	for (loop_counter = 0; loop_counter < code_high_digit; loop_counter++) {
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_SET);
		vTaskDelay(blink_interval/portTICK_RATE_MS);
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_RESET);
		vTaskDelay(blink_interval/portTICK_RATE_MS);
	}
	vTaskDelay(digit_interval/portTICK_RATE_MS);
	for (loop_counter = 0; loop_counter < code_low_digit; loop_counter++) {
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_SET);
		vTaskDelay(blink_interval/portTICK_RATE_MS);
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_RESET);
		vTaskDelay(blink_interval/portTICK_RATE_MS);
	}
	vTaskDelay(time_offset/portTICK_RATE_MS);
}
