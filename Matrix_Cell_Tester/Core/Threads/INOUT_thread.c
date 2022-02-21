/*
 * LCD.c
 *
 *  Created on: 08.11.2018
 *      Author: user
 */
#include "INOUT_thread.h"
#include "INOUT.h"

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
uint16_t analogs[8];

uint16_t buffered_read[100];

uint8_t adress = 0;

void INOUT_task(void const * argument)
{

	//boot_wifi();



	HAL_ADC_Start_DMA(&hadc,(uint32_t *)&IN_adc[0],8);

	//osDelay(400);

	for(;;)
	{
		adress = h_adress();


		if(adress == RX_Frame.Adress && RX_Frame.do_it == 1)
		{

			Set_Out(RX_Frame.OUT,RX_Frame.Mode);
			RX_Frame.do_it = 0;
			TX_Frame.State = 0x01;
			TX_Frame.Adress = adress;

			HAL_GPIO_WritePin(WORK_GPIO_Port,WORK_Pin,GPIO_PIN_RESET);
			if(RX_Frame.frame_count > 0 && RX_Frame.frame_count <= 100 && RX_Frame.Mode & 0x01)
			{
				if( RX_Frame.OUT <= 8 && RX_Frame.OUT > 0 )
				{

				uint16_t crc_to_send = 0;
				uint8_t frame_to_send[20]={'s'};


				for(uint16_t c=0; c< RX_Frame.frame_count;c++)
				{
					osDelay(RX_Frame.frame_Tstamp);
					buffered_read[c] = analogs[(RX_Frame.OUT)-1];
				}



				}
			HAL_GPIO_WritePin(WORK_GPIO_Port,WORK_Pin,GPIO_PIN_SET);
			send_frame(RX_Frame.frame_count, ANALOG_SEND);

			}
			TX_Frame.State = 0x00;
			send_frame(1,STATE_SEND);

		}

		osDelay(1);

	}


}






void send_frame (uint16_t frame_cnt, uint8_t mode)
{


	for(uint16_t c=0; c< frame_cnt;c++)
	{

		HAL_GPIO_TogglePin(WORK_GPIO_Port,WORK_Pin);
		if(mode == ANALOG_SEND)
		{
		TX_Frame.MADC = buffered_read[c];
		TX_Frame.frame_count = c;
		}

		if(mode == STATE_SEND)
		{
			TX_Frame.MADC = 0;
			TX_Frame.frame_count = 0;
		}


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

	HAL_GPIO_WritePin(WORK_GPIO_Port,WORK_Pin,GPIO_PIN_SET);


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

	memcpy(analogs,IN_adc,16);
//HAL_ADC_Start_DMA(&hadc,IN_adc,8);

}




