/*
 * LCD.c
 *
 *  Created on: 08.11.2018
 *      Author: user
 */
#include "INOUT_thread.h"

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"
#include "CMD_thread.h"
#include "variables.h"


extern xQueueHandle usr_serial_rx_queue;

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc;

extern TIM_OC_InitTypeDef sConfigOC;

char char_[30];

void INOUT_task(void const * argument)
{

	//boot_wifi();

	HAL_ADC_Start_DMA(&hadc,(uint32_t*)IN_adc,8);



	//osDelay(400);

	for(;;)
	{
		if(h_adress() == RX_Frame.Adress && RX_Frame.do_it == 1)
		{

			Set_Out(RX_Frame.OUT);
			RX_Frame.do_it = 0;


			if(RX_Frame.frame_count > 0)
			{
				uint16_t crc_to_send = 0;
				uint8_t frame_to_send[20]={'s'};

				for(uint8_t c=0; c< RX_Frame.frame_count;c++)
				{
					TX_Frame.Adress = RX_Frame.Adress;
					TX_Frame.frame_count = c;
					TX_Frame.State = 0x01;
					TX_Frame.MADC = IN_adc[(RX_Frame.OUT & 0xf)-1];

					send_frame();

					osDelay(RX_Frame.frame_Tstamp);
				}

			}



		}

		osDelay(1);

	}


}

void Set_Out(uint8_t data)
{

	if(data & 0x20)
	{

		if(data & 1)
		{
			HAL_GPIO_WritePin(SET_OUT_1_GPIO_Port, SET_OUT_1_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_1_GPIO_Port, SET_OUT_1_Pin, GPIO_PIN_RESET);
		}


		if(data & 2)
		{
			HAL_GPIO_WritePin(SET_OUT_2_GPIO_Port, SET_OUT_2_Pin, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_2_GPIO_Port, SET_OUT_2_Pin, GPIO_PIN_RESET);
		}



	}




}




void send_frame (void)
{
	memset(char_,0,30);
	sprintf(char_,"s%2X%4X%2X%4X",TX_Frame.Adress,TX_Frame.frame_count,TX_Frame.State,TX_Frame.MADC);
	string_zero_fill(&char_);
	TX_Frame.CRC_sum = 0;
	TX_Frame.CRC_sum = calc_crc(&char_[1],12);
	memset(char_,0,30);
	sprintf(char_,"s%2X%4X%2X%4X%4Xz",TX_Frame.Adress,TX_Frame.frame_count,TX_Frame.State,TX_Frame.MADC,TX_Frame.CRC_sum);
	string_zero_fill(&char_);
	serial_send_string(&char_);
}


uint8_t h_adress(void)
{

	uint8_t temp_adr = 0;

	if(!HAL_GPIO_ReadPin(CH1_GPIO_Port,CH1_Pin))
	{
		temp_adr = temp_adr | 0x01;
	}

	if(!HAL_GPIO_ReadPin(CH2_GPIO_Port,CH2_Pin))
	{
		temp_adr = temp_adr | 0x02;
	}

	if(!HAL_GPIO_ReadPin(CH3_GPIO_Port,CH3_Pin))
	{
		temp_adr = temp_adr | 0x04;
	}

	if(!HAL_GPIO_ReadPin(CH4_GPIO_Port,CH4_Pin))
	{
		temp_adr = temp_adr | 0x08;
	}

	return temp_adr;

}


uint8_t c = 0;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{

HAL_ADC_Start_DMA(&hadc,(uint32_t*)IN_adc,8);

}




