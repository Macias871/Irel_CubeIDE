/*
 * INOUT.c
 *
 *  Created on: 9 lut 2022
 *      Author: Irel
 */
#include "INOUT.h"

	uint8_t data_1 =0;
	uint8_t data_2 =0;
	uint8_t data_3 =0;

void Set_Out(uint8_t data, uint8_t mode)
{





	if(mode == 0x10 )
	{
		mode = 0x0E;
		data = 0;
	}


	if(mode & 0x02)
	{
		data_1 = data;

		if(data & 0x1)
		{
			HAL_GPIO_WritePin(SET_OUT_1_GPIO_Port, SET_OUT_1_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_1_GPIO_Port, SET_OUT_1_Pin, GPIO_PIN_SET);
		}


		if(data & 0x2)
		{
			HAL_GPIO_WritePin(SET_OUT_2_GPIO_Port, SET_OUT_2_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_2_GPIO_Port, SET_OUT_2_Pin, GPIO_PIN_SET);
		}

		if(data & 0x4)
		{
			HAL_GPIO_WritePin(SET_OUT_3_GPIO_Port, SET_OUT_3_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_3_GPIO_Port, SET_OUT_3_Pin, GPIO_PIN_SET);
		}

		if(data & 0x8)
		{
			HAL_GPIO_WritePin(SET_OUT_4_GPIO_Port, SET_OUT_4_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_4_GPIO_Port, SET_OUT_4_Pin, GPIO_PIN_SET);
		}

		if(data & 0x10)
		{
			HAL_GPIO_WritePin(SET_OUT_5_GPIO_Port, SET_OUT_5_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_5_GPIO_Port, SET_OUT_5_Pin, GPIO_PIN_SET);
		}

		if(data & 0x20)
		{
			HAL_GPIO_WritePin(SET_OUT_6_GPIO_Port, SET_OUT_6_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_6_GPIO_Port, SET_OUT_6_Pin, GPIO_PIN_SET);
		}

		if(data & 0x40)
		{
			HAL_GPIO_WritePin(SET_OUT_7_GPIO_Port, SET_OUT_7_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_7_GPIO_Port, SET_OUT_7_Pin, GPIO_PIN_SET);
		}

		if(data & 0x80)
		{
			HAL_GPIO_WritePin(SET_OUT_8_GPIO_Port, SET_OUT_8_Pin, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(SET_OUT_8_GPIO_Port, SET_OUT_8_Pin, GPIO_PIN_SET);
		}



		if(mode & 0x04)
		{

			data_2 = data;

			if(data & 0x01)
			{
				HAL_GPIO_WritePin(DIVIDER_1_GPIO_Port, DIVIDER_1_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_1_GPIO_Port, DIVIDER_1_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x02)
			{
				HAL_GPIO_WritePin(DIVIDER_2_GPIO_Port, DIVIDER_2_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_2_GPIO_Port, DIVIDER_2_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x04)
			{
				HAL_GPIO_WritePin(DIVIDER_3_GPIO_Port, DIVIDER_3_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_3_GPIO_Port, DIVIDER_3_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x08)
			{
				HAL_GPIO_WritePin(DIVIDER_4_GPIO_Port, DIVIDER_4_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_4_GPIO_Port, DIVIDER_4_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x10)
			{
				HAL_GPIO_WritePin(DIVIDER_5_GPIO_Port, DIVIDER_5_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_5_GPIO_Port, DIVIDER_5_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x20)
			{
				HAL_GPIO_WritePin(DIVIDER_6_GPIO_Port, DIVIDER_6_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_6_GPIO_Port, DIVIDER_6_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x40)
			{
				HAL_GPIO_WritePin(DIVIDER_7_GPIO_Port, DIVIDER_7_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_7_GPIO_Port, DIVIDER_7_Pin, GPIO_PIN_RESET);
			}

			if(data & 0x80)
			{
				HAL_GPIO_WritePin(DIVIDER_8_GPIO_Port, DIVIDER_8_Pin, GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(DIVIDER_8_GPIO_Port, DIVIDER_8_Pin, GPIO_PIN_RESET);
			}


		}

		if(mode & 0x08)
		{

			data_3 = data;

			if(data & 0x01)
			{
				HAL_GPIO_WritePin(MUL_1_GPIO_Port, MUL_1_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_1_GPIO_Port, MUL_1_Pin, GPIO_PIN_SET);
			}

			if(data & 0x02)
			{
				HAL_GPIO_WritePin(MUL_2_GPIO_Port, MUL_2_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_2_GPIO_Port, MUL_2_Pin, GPIO_PIN_SET);
			}

			if(data & 0x04)
			{
				HAL_GPIO_WritePin(MUL_3_GPIO_Port, MUL_3_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_3_GPIO_Port, MUL_3_Pin, GPIO_PIN_SET);
			}

			if(data & 0x08)
			{
				HAL_GPIO_WritePin(MUL_4_GPIO_Port, MUL_4_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_4_GPIO_Port, MUL_4_Pin, GPIO_PIN_SET);
			}

			if(data & 0x10)
			{
				HAL_GPIO_WritePin(MUL_5_GPIO_Port, MUL_5_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_5_GPIO_Port, MUL_5_Pin, GPIO_PIN_SET);
			}

			if(data & 0x20)
			{
				HAL_GPIO_WritePin(MUL_6_GPIO_Port, MUL_6_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_6_GPIO_Port, MUL_6_Pin, GPIO_PIN_SET);
			}

			if(data & 0x40)
			{
				HAL_GPIO_WritePin(MUL_7_GPIO_Port, MUL_7_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_7_GPIO_Port, MUL_7_Pin, GPIO_PIN_SET);
			}

			if(data & 0x80)
			{
				HAL_GPIO_WritePin(MUL_8_GPIO_Port, MUL_8_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(MUL_8_GPIO_Port, MUL_8_Pin, GPIO_PIN_SET);
			}

		}

	}




}
