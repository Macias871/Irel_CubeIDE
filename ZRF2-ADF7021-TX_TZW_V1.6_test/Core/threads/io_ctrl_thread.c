

#include <stdint.h>
//#include "../init/gpio_init.h"

#include "../threads/io_ctrl_thread.h"
//#include "../assert.hpp"
//#include "../config.h"
#include "variables.h"
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
//#include "../stm32f10x.h"
#include "main.h"
#include "../lib/CRC.h"
#include "../lib/ADC.h"

extern ADC_HandleTypeDef hadc;
extern SPI_HandleTypeDef hspi2;
uint8_t sbo[30];
uint8_t sbi[30];
uint8_t end_of_dig = 32;

uint8_t tmp_tab[24];
uint8_t frame_digit[30];
uint8_t analog_tab[10];
uint8_t FRAME_SPI_TX[10]={0,0,0,1,0,0,0,0,0,0};
#define TYP_EXP 0x86

uint8_t inputs_array[128];

uint8_t num = 0;


volatile uint8_t bad_crc = 1;
uint8_t bad_crc_count = 0;
volatile uint8_t srv_key_stage = 0;

void io_ctrl_task(void const * argument)
{


	uint8_t loop_counter = 0;

	volatile uint8_t io_local_off_counter_reset = 0;
	uint8_t ask_tab[30];





	  for(;;)
	  {

			HAL_ADC_Start_DMA(&hadc,(uint32_t*)&system_adc_values[0],anal_count);

		  if(programmode == 0 && !(error_code & CFG_CRC_ERR_BIT))
		  {

		  if (xSemaphoreTake(off_counter_reset_mutex, (portTickType) 10) == pdTRUE) {
			  io_local_off_counter_reset = off_counter_reset_glob;
		  		}
		 		xSemaphoreGive(off_counter_reset_mutex);

		  		for (loop_counter = 0U; loop_counter < 64U; loop_counter++) {

		  			if((1 << gpio_pins_array[loop_counter]) != 0xFE)
		  			{
		  				if ((gpio_port_array[loop_counter]->IDR & (1 << gpio_pins_array[loop_counter])) && (1 << gpio_pins_array[loop_counter]) != 0xff) {
		  					inputs_array[loop_counter] = 0U;
		  				}
		  				else {
		  					inputs_array[loop_counter] = 1U;
		  				}
		  			}
		  			else
		  			{

		  			}
		  		}

//***************************************************************************************************************************************************************************//SPI

	  			//if(tx_cfg.spi_cfg[num] > 0 && tx_cfg.spi_cfg[1+num] == 0x86 )			//0x86 oled
	  			//{spi_n((num/2)+1,0x86,6,FRAME_SPI_TX);}


	  			for(int pos = 0; pos < 8; pos = pos + 2)
	  			{
	  			if(tx_cfg.spi_cfg[pos] > 0 && tx_cfg.spi_cfg[1+pos] == 0x01)			//0x01 wejscia  //bajty 5,4,3
	  			{
	  				uint8_t start = tx_cfg.spi_cfg[pos];
	  				uint8_t stop= 20 + tx_cfg.spi_cfg[pos];



	  				bad_crc = spi_n((pos/2)+1,0x86,6,ask_tab);
	  				if(bad_crc == 0)
	  				{
	  				bad_crc_count = 0;
	  				uint8_t byte_num = 0;

	  				for(uint8_t c = 1; c < 4; c++){
	  					if(sbi[c] & (uint8_t)(0x01)){tmp_tab[byte_num +0] = 1; }else{tmp_tab[byte_num +0] = 0;}
	  					if(sbi[c] & (uint8_t)(0x02)){tmp_tab[byte_num +1] = 1; }else{tmp_tab[byte_num +1] = 0;}
	  					if(sbi[c] & (uint8_t)(0x04)){tmp_tab[byte_num +2] = 1; }else{tmp_tab[byte_num +2] = 0;}
	  					if(sbi[c] & (uint8_t)(0x08)){tmp_tab[byte_num +3] = 1; }else{tmp_tab[byte_num +3] = 0;}
	  					if(sbi[c] & (uint8_t)(0x10)){tmp_tab[byte_num +4] = 1; }else{tmp_tab[byte_num +4] = 0;}
	  					if(sbi[c] & (uint8_t)(0x20)){tmp_tab[byte_num +5] = 1; }else{tmp_tab[byte_num +5] = 0;}
	  					if(sbi[c] & (uint8_t)(0x40)){tmp_tab[byte_num +6] = 1; }else{tmp_tab[byte_num +6] = 0;}
	  					if(sbi[c] & (uint8_t)(0x80)){tmp_tab[byte_num +7] = 1; }else{tmp_tab[byte_num +7] = 0;}
	  					byte_num = byte_num + 8;
	  				}
	  				uint8_t cnt_tmp = 0;

  					for(uint8_t d = start; d < stop;d++)
  						{
  						inputs_array[d] = tmp_tab[cnt_tmp];
  						cnt_tmp++;

  						}
	  				}
	  				else
	  				{
	  					bad_crc_count++;

	  					if(bad_crc_count > 3)
	  					{
	  						bad_crc_count = 0;
	  					for(uint8_t d = start; d < stop;d++)
	  						{
	  						inputs_array[d] = 0;
	  						}
	  					}
	  				}
	  			}


	  			if(tx_cfg.spi_cfg[pos] > 0 && tx_cfg.spi_cfg[1+pos] == 0x86)				//0x86 oled
	  			{
	  				rx_frame[3] = RSSI;
	  				spi_n((pos/2)+1,0x86,10,&rx_frame[2]);

	  			}


	  			}


				  /**************  SRV key  ***************/

				  if (inputs_array[tx_cfg.srv_key[0]] == 0U && inputs_array[tx_cfg.srv_key[1]] == 0U){
					  srv_key_stage = 0;
					  SRV_BYTE &=~SRV_ACTIVE;
				  }

				  if (inputs_array[tx_cfg.srv_key[1]] == 1U && srv_key_stage == 0){
					  srv_key_stage = 1; }
				  if (inputs_array[tx_cfg.srv_key[0]] == 1U && srv_key_stage == 1){
					  srv_key_stage = 2; }
				  if (inputs_array[tx_cfg.srv_key[1]] == 0U && srv_key_stage == 2){
					  srv_key_stage = 3; }


				  if(srv_key_stage == 3)
				  {
					  SRV_BYTE |= SRV_ACTIVE;
					  if (inputs_array[tx_cfg.srv_key[3]] == 1U){
						  SRV_BYTE |= SRV_MIN; }else{SRV_BYTE &=~SRV_MIN;}

					  if (inputs_array[tx_cfg.srv_key[1]] == 1U){
						  SRV_BYTE |= SRV_PLUS; }else{SRV_BYTE &=~SRV_PLUS;}

					  if (inputs_array[tx_cfg.srv_key[2]] == 1U){
						  SRV_BYTE |= SRV_MINUS; }else{SRV_BYTE &=~SRV_MINUS;}

				  }
				  /**************  SRV key  ***************/


				  /**************  Extra frame add  ***************/
				  for(uint8_t b = 0; b < 8; b++)
				  {
					  if(SRV_BYTE & (1 << b)){
					  inputs_array[120+b] = 1 ;}
					  else
					  {
						  inputs_array[120+b] = 0;
					  }
				  }
				  /**************  Extra frame add  ***************/



//***************************************************************************************************************************************************************************//SPI

		  		if (xSemaphoreTake(tx_frame_mutex, (portTickType) 10) == pdTRUE) {
		  			for (loop_counter = 0U; loop_counter < 128U; loop_counter++) {
		  				if ((tx_cfg.ktab_cnv[loop_counter].pin_no == 0xFF)  || (tx_cfg.ktab_cnv[loop_counter].bit_no == 0xFF)) {
		  					break;
		  				}
		  				else {
		  					if ((tx_cfg.ktab_cnv[loop_counter].flags & KEY_CFG_OUTPUT)) 			//Tryb wyjscia pinu
		  					{
		  						//if(loop_counter < 64){gpio_pins_array[loop_counter] = PIN_OUTPUT;}
		  						inputs_array[tx_cfg.ktab_cnv[loop_counter].pin_no] = 0;
		  					}
		  					else{																	//Tryb wejscia pinu
		  						if ((tx_cfg.ktab_cnv[loop_counter].flags & KEY_CFG_INVERT)) {		//Odwrocenie stanu
		  							if (inputs_array[tx_cfg.ktab_cnv[loop_counter].pin_no] == 1) {
		  								inputs_array[tx_cfg.ktab_cnv[loop_counter].pin_no] = 0;
		  							}
		  							else {
		  								inputs_array[tx_cfg.ktab_cnv[loop_counter].pin_no] = 1;
		  							}

		  						}
		  					}


		  					frame_change_bit(inputs_array, tx_cfg.ktab_cnv[loop_counter].pin_no, frame_digit, tx_cfg.ktab_cnv[loop_counter].bit_no);

		  					if(frame_digit[0] & (uint8_t)(0x01)){BB_STOP = 1; }else{BB_STOP = 0;}
		  					if(frame_digit[0] & (uint8_t)(0x02)){BB_START = 1;}else{BB_START = 0;}




		  					if (inputs_array[tx_cfg.ktab_cnv[loop_counter].pin_no] == 1) {
		  						if ((tx_cfg.ktab_cnv[loop_counter].flags & KEY_CFG_OFF_RESET) == 0) {


		  						}
		  						else
		  						{
		  							io_local_off_counter_reset = 1;
		  						}
		  					}
		  				}
		  			}



		  			tx_frame[0] = SRV_BYTE;

		  			for(int c = 1; c < tx_cfg.byte_offset+1; c++)
		  			{
		  				tx_frame[c] = analog_tab[c-1];
		  			}


		  			for(int c = tx_cfg.byte_offset+1; c < tx_cfg.tx_len+tx_cfg.byte_offset+1; c++ )
		  			{
		  				tx_frame[c] = frame_digit[c-(tx_cfg.byte_offset+1)];
		  			}






		  		}
		  		xSemaphoreGive(tx_frame_mutex);

		  		if (xSemaphoreTake(off_counter_reset_mutex, (portTickType) 10) == pdTRUE) {
		  			off_counter_reset_glob = io_local_off_counter_reset;
		  		}
		  		xSemaphoreGive(off_counter_reset_mutex);

		  		osDelay(20);

	  }
		  else
		  {
			  osDelay(100);
		  }

	  }



	}

uint8_t frame_change_bit(
	uint8_t * const input_table,
	const uint8_t input_table_possiton,
	uint8_t * const frame,
	const uint8_t frame_bit_possition
) {
	uint8_t frame_byte_possition = 0U;
	uint8_t byte_bit_possition = 0U;

	frame_byte_possition = frame_bit_possition / 8U;
	byte_bit_possition = frame_bit_possition % 8U;

	if (input_table[input_table_possiton] == 1U) {
		frame[frame_byte_possition] |= (1 << byte_bit_possition);
	}
	else {
		frame[frame_byte_possition] &=~ (1 << byte_bit_possition);
	}
	return 0;
}


uint8_t spi_n(uint8_t n, uint8_t t, uint8_t l, uint8_t *b)
{
// n - numer rozszerzenia SPI
// t - typ rozszerzenia SPI
// l - dlugosc ramki bez CRC
// b - wskaznik do tablicy z danymi

//	uint8_t rx_ok = 0;

	  sbo[0] = t;

	  for(int c = 0; c < l; c++)
	  {
		  sbo[c+1] = b[c];
	  }

	  uint16_t crc = 0xffff;
	  crc = calc_crc(sbo, l);
	  *(uint16_t *)&sbo[l] = crc;


	  if(tx_settings.spi_cnt > 0)
	  {
	  if(n==1){HAL_GPIO_WritePin(SS1_GPIO_Port,SS1_Pin,RESET);}
	  if(n==2){HAL_GPIO_WritePin(SS2_GPIO_Port,SS1_Pin,RESET);}
	  if(n==3){HAL_GPIO_WritePin(SS3_GPIO_Port,SS1_Pin,RESET);}
	  if(n==4){HAL_GPIO_WritePin(SS4_GPIO_Port,SS1_Pin,RESET);}


	  for(uint16_t c = 0; c < 300; c++)
	  {
		  asm ("nop");
	  }
	  //HAL_SPI_TransmitReceive_DMA(&hspi2,sbo,sbi,l+4);


	  HAL_SPI_TransmitReceive(&hspi2,sbo,sbi,l+2,10);

/*
	  for(int f = 0; f < l+2; f++)
	  {

		  HAL_SPI_TransmitReceive(&hspi2,&sbo[f],&sbi[f],1,20);
	  }
*/



   	  if(n==1){HAL_GPIO_WritePin(SS1_GPIO_Port,SS1_Pin,SET);}
   	  if(n==2){HAL_GPIO_WritePin(SS2_GPIO_Port,SS1_Pin,SET);}
   	  if(n==3){HAL_GPIO_WritePin(SS3_GPIO_Port,SS1_Pin,SET);}
   	  if(n==4){HAL_GPIO_WritePin(SS4_GPIO_Port,SS1_Pin,SET);}


   	  /*
   	  for(uint8_t rest = 0; rest < 8; rest++)
   	  {
   	  volatile uint8_t rest_me = 0;
   	  rest_me = SPI1->DR;

   	  }
   	  */

	  }


	  if((*(uint16_t *)&sbi[l+2]) != (calc_crc(sbi, l+2)))
	  {

	      return 1;
	  }
	  else
	  {


		  return 0;
	  }

}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
{
	  bat_voltage = system_adc_values[0];

		for(uint8_t c = 1 ; c < anal_count;c++)
		{
			analog_tab[c] = system_adc_values[c]/16;
		}



}
