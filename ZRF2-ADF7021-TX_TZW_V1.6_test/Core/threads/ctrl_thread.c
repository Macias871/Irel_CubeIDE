

#include <stdint.h>
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"
#include "../lib/eeprom.h"
#include "../threads/ctrl_thread.h"
#include "../ADF7021/adf7021.h"

#include "../../config.h"
#include "variables.h"

uint32_t off_time_counter = 0U;

extern osThreadId radio_threadHandle;
extern osThreadId io_ctrl_threadHandle;
extern osThreadId ctrl_threadHandle;


enum {
BATTERY_LEVEL_LOW = 0,
BATTERY_LEVEL_MEDIUM = 1,
BATTERY_LEVEL_HIGH = 2
} battery_level = BATTERY_LEVEL_LOW;

void ctrl_task(void const * argument) {

	  HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_SET);




		if (1 == check_crc_eeprom()) {
			error_code |= CFG_CRC_ERR_BIT;}
		else{error_code &=~ CFG_CRC_ERR_BIT;}

	while(error_code & CFG_CRC_ERR_BIT)
	{

		vTaskDelay(100/portTICK_RATE_MS);
		if (error_code & CFG_CRC_ERR_BIT) {
			blink_error_code(33, LEDR_GPIO_Port, LEDR_Pin, 100U, 100U, 1500U);
		}
	}


if(tx_cfg.fb_len == 0)
{
	programmode = 2;
}



		  	uint32_t status_led_counter = 0U;
		  	uint32_t no_program_off = 0U;

		  	uint8_t local_off_counter_reset = 0;
		  //	uint16_t local_battery_values[10];
		  //	uint8_t local_battery_value_counter = 0;
		//  	uint16_t local_battery_mean_value = 0;
//		  	uint8_t function_status = 0;
		  	enum {
		  		BATTERY_LEVEL_LOW = 0,
		  		BATTERY_LEVEL_MEDIUM = 1,
		  		BATTERY_LEVEL_HIGH = 2
		  	} battery_level = BATTERY_LEVEL_LOW;



		  	error_code = (CFG_VER_ERR_BIT | CFG_LEN_ERR_BIT );

		  	if (tx_cfg.cfg_ver == CFG_VERSION_M || tx_cfg.cfg_ver == CFG_VERSION_D ) {
		  		error_code &=~ CFG_VER_ERR_BIT;

		  		if(tx_cfg.cfg_ver == CFG_VERSION_D)
		  		{
		  			SYS_LOW_BATTERY_LEVEL = SYS_LOW_BATTERY_LEVEL_D;
		  			SYS_HIGH_BATTERY_LEVEL = SYS_HIGH_BATTERY_LEVEL_D;
		  		}

		  		if(tx_cfg.cfg_ver == CFG_VERSION_M)
		  		{
		  			SYS_LOW_BATTERY_LEVEL = SYS_LOW_BATTERY_LEVEL_M;
		  			SYS_HIGH_BATTERY_LEVEL = SYS_HIGH_BATTERY_LEVEL_M;
		  		}


		  	}
		  	if (tx_cfg.fb_len != 0xFFFF) {
		  		error_code &=~ CFG_LEN_ERR_BIT;
		  	}
		  	// TODO checking for CRC error
		  	//error_code &=~ CFG_CRC_ERR_BIT;







		  	for(;;) {


				if (no_program_off < 20) {
					no_program_off++;
	  			}else {
	  				//HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
	  				Turn_OFF(tx_cfg.TOFFE);
	  			}




					if (error_code & CFG_VER_ERR_BIT) {
						blink_error_code(12, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 600U);
					}
					if (error_code & CFG_LEN_ERR_BIT) {
						blink_error_code(15, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 600U);
					}
					if (error_code & CFG_CRC_ERR_BIT) {
						blink_error_code(31, LEDR_GPIO_Port, LEDR_Pin, 200U, 400U, 600U);
					}
					if (error_code == 0) {
						break;
					}

				vTaskDelay(50/portTICK_RATE_MS);


		  		}




	  	 for(;;) {

	  		if(programmode == 0 && !(SRV_BYTE & SRV_ACTIVE) && setup_flag == 0)
	  		{


		  		osDelay(10);
		  		if (xSemaphoreTake(off_counter_reset_mutex, (portTickType) 10) == pdTRUE) {
		  			local_off_counter_reset = off_counter_reset_glob;
		  			//off_counter_reset = 0;
		  		}
		  		xSemaphoreGive(off_counter_reset_mutex);


		  		if (status_led_counter < STATUS_LED_BLINK_INTERVAL) {
		  			status_led_counter++;
		  		}
		  		else {
		  			status_led_counter = 0U;
		  			if (bat_voltage < SYS_LOW_BATTERY_LEVEL) {
		  				battery_level = BATTERY_LEVEL_LOW;
		  			}
		  			else {
		  				if (bat_voltage < SYS_HIGH_BATTERY_LEVEL) {
		  					battery_level = BATTERY_LEVEL_MEDIUM;
		  				}
		  				else {
		  					battery_level = BATTERY_LEVEL_HIGH;
		  				}
		  			}

		  			switch (battery_level) {
		  			case BATTERY_LEVEL_LOW:
		  				HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
		  				HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,SET);
		  				osDelay(50);
		  				HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);

							  SRV_BYTE |= BAT_L;
							  SRV_BYTE &=~ BAT_M;
							  SRV_BYTE &=~ BAT_H;

		  				break;
		  			case BATTERY_LEVEL_MEDIUM:
		  				HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,SET);
		  				HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,SET);

		  				osDelay(50);
		  				HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);
		  				HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);

		  				SRV_BYTE |= BAT_M;
		  				SRV_BYTE &=~ BAT_L;
		  				SRV_BYTE &=~ BAT_H;

		  				break;
		  			case BATTERY_LEVEL_HIGH:
		  				HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,SET);
		  				osDelay(50);
		  				HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);

		  				HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);

		  				SRV_BYTE |= BAT_H;
		  				SRV_BYTE &=~ BAT_L;
		  				SRV_BYTE &=~ BAT_M;

		  				break;
		  			default:
		  				break;
		  			}
		  		}


		  		/**
		  		 * @brief Power down when stop is pulled, after off_time2 elapsed.
		  		 */

		  		if (BB_STOP == 1) {
		  			if (stop_counter < (tx_cfg.off_time2 * 100U)) {
		  				stop_counter++;
		  			}
		  			else {
		  				//HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
		  				Turn_OFF(tx_cfg.TOFFE);
		  			}
		  		}
		  		else {
		  			stop_counter = 0;
		  		}

		  		/**
		  		 * @brief Power of when off_time3 elapsed, when battery level is low
		  		 * or off_time1, when battery level isn't low.
		  		 */
		  		if (local_off_counter_reset == 0) {




		  		}
		  		else {
		  			off_time_counter = 0;
		  		}
		  		if (battery_level == BATTERY_LEVEL_LOW) {
		  			if (off_time_counter > (tx_cfg.off_time3 * 100U)) {
		  				vTaskDelay(100/portTICK_RATE_MS);
		  				//HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
		  				Turn_OFF(tx_cfg.TOFFE);
		  				vTaskDelay(100/portTICK_RATE_MS);
		  			}
		  		}
		  		else {
		  			if (off_time_counter > (tx_cfg.off_time1 * 100U)) {
		  				vTaskDelay(100/portTICK_RATE_MS);
		  				//HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
		  				Turn_OFF(tx_cfg.TOFFE);
		  				vTaskDelay(100/portTICK_RATE_MS);
		  			}
		  		}
		  	}
		  	else
		  	{
				if (stop_counter < (tx_cfg.off_time1 * 100U)) {
	  				stop_counter++;
	  			}
	  			else {
	  				//HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
	  				Turn_OFF(tx_cfg.TOFFE);
	  			}

				if(setup_flag == 0)						//Ustawianie analogow
				{

					HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin,RESET);
					HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin,RESET);


					if(SRV_BYTE & SRV_MINUS){
						HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin,SET);
					}

					if(SRV_BYTE & SRV_PLUS){
						HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin,SET);
					}


					if(SRV_BYTE & SRV_MIN)
					{
						HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,SET);
						HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);
					}
					else
					{
						HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
						HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,SET);
					}
				}
				else
				{

														//Ustawianie kanalow
				}
				vTaskDelay(20/portTICK_RATE_MS);
				//blink_error_code(12, LEDR_GPIO_Port, LEDR_Pin, 40U, 40U, 300U);
		  	}



	  		if (xSemaphoreTake(off_counter_reset_mutex, (portTickType) 10) == pdTRUE) {
	  			local_off_counter_reset = 0;
	  			off_counter_reset_glob = local_off_counter_reset;
	  			//off_counter_reset = 0;
	  		}
	  		xSemaphoreGive(off_counter_reset_mutex);



		  }

}

void Turn_OFF(uint8_t mode)
{
	if(mode == 0)
	{
		//HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
	}
	if(mode == 1)
	{
		HAL_GPIO_WritePin(POFF_GPIO_Port,POFF_Pin,GPIO_PIN_RESET);
		adf_set_power_off();
		osThreadSuspend(radio_threadHandle);
		osThreadSuspend(io_ctrl_threadHandle);
		osThreadSuspend(ctrl_threadHandle);
		for(;;)
		{
			HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,GPIO_PIN_RESET);

		}
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
		osDelay(blink_interval);
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_RESET);
		osDelay(blink_interval);
	}
	osDelay(digit_interval);
	for (loop_counter = 0; loop_counter < code_low_digit; loop_counter++) {
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_SET);
		osDelay(blink_interval);
		HAL_GPIO_WritePin(led_port,led_pin,GPIO_PIN_RESET);
		osDelay(blink_interval);
	}
	osDelay(time_offset);
}
