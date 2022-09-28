#include <stdint.h>
#include <string.h>
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "../threads/radio_thread.h"
#include "../threads/io_ctrl_thread.h"
#include "variables.h"
#include "config.h"
#include "main.h"
#include "../threads/threads.h"
#include "../ADF7021/adf7021.h"
#include "../Src/pk_functions.h"
#include "../lib/xprintf.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

int8_t Rssi;
uint8_t tx_buffer[30] = {0};
uint8_t rx_buffer[30] = {0};
uint8_t rx_data[30];
uint8_t tx_data[30];

uint8_t temp_tx_data[30];

uint8_t rx_channel_tab_num =7;
uint16_t rx_unit_number = 0;
uint16_t counter_rssi = 0;
uint8_t check_channel_routine =0;
uint16_t rx_number = 0;
uint16_t rx_loop_counter = 0;
uint16_t search_loop_counter = 0;


volatile FlagStatus xRxTimeout = RESET;

extern enum _ACTUAL_RADIO_STATE ACTUAL_RADIO_STATE;
extern SPI_HandleTypeDef hspi3;

volatile uint16_t radio_frame_crc = 0xFFFF;
volatile uint32_t freq_ch;
volatile uint32_t freq;
volatile uint8_t rxBytes;
xSemaphoreHandle RadioSpi_mutex;

volatile uint8_t rx_ok = 0;
uint8_t rx_cnt = 0;
uint16_t RX_Delay = 0;



extern uint8_t RX_RF_Frame_out[30];
void radio_task(void const * argument){

	RX_FRAME_LENGHT = rx_cfg.rx_len + 5;
	TX_FRAME_LENGHT = rx_cfg.tx_len + 5;

	memset(tx_buffer, 0, TX_FRAME_LENGHT);
	adf_reset();


	rx_channel_tab_num = 6;

	//adf_simple_init();
	 set_channel(rx_channel_tab_num,ADF_RX_MODE);
	 set_power(3);

	  RX_Delay = 10 + 2*RX_FRAME_LENGHT;



for(;;) {

	if (system_errors.cfg_crc != 1 && programmode == 0){




		if(check_channel_routine == 1)
		{
			//Search_channel();
		}


		if(REC_PACKET(RX_FRAME_LENGHT, rx_channel_tab_num,RX_Delay, check_channel_routine ))
		{
			//read_back = adf_readback_voltage();
			check_channel_routine = 0;
			Decode_RX_Packet();
			if(rx_cfg.tx_len > 0)
			{
//			Code_TX_Packet();
//			SEND_PACKET(tx_data, TX_FRAME_LENGHT, rx_channel_tab_num);
			}
		}
		else
		{

			osDelay(1);
		}

	}




	if(rx_loop_counter >= 500 && check_channel_routine == 0 )		//Po 0,5s roz��cza k1k2
	{
		radio_status = 0;
		HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
	}

	if(rx_loop_counter >= 2000 && check_channel_routine == 0 )		// Po 2s szuka kanalow
	{
		rx_loop_counter = 0;
		counter_rssi = 0;
		check_channel_routine = 1;


	}


	}
}



void Search_channel(void)
{

	if(rx_channel_tab_num < 7)
	{
		rx_channel_tab_num++;
	}
	else
	{
		rx_channel_tab_num =0;
	}


}





void Decode_RX_Packet()
{
	memcpy(rx_buffer,RX_RF_Frame_out,RX_FRAME_LENGHT);

						rxBytes = rx_cfg.rx_len;
						uint16_t radio_frame_crc = 0xFFFF;
  						for (int loop_counter = 0; loop_counter < rxBytes - 2; loop_counter++) {
  							radio_frame_crc = crc_update(radio_frame_crc, rx_buffer[loop_counter]);
  						}

  						if (radio_frame_crc == ((rx_buffer[rxBytes - 1] << 8) | rx_buffer[rxBytes - 2]))		//Je�li crc ok
  						{
  							rx_number = (rx_buffer[1] << 8) | (rx_buffer[0]);
  							if ( rx_number == rx_cfg.dev_no[0] || rx_number == rx_cfg.dev_no[1] || rx_number == rx_cfg.dev_no[2] || rx_number == rx_cfg.dev_no[3] || rx_number == rx_cfg.dev_no[4] || rx_number == rx_cfg.dev_no[5] || rx_number == rx_cfg.dev_no[6] || rx_number == rx_cfg.dev_no[7]){
  							memset(rx_frame, 0, rxBytes - 2);
  							memcpy(rx_frame, &rx_buffer[3], rxBytes - 3);

  					    	HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,SET);

  					    	//RSSI = adf_readback_rssi();


  						    radio_status = 1;
  						    rx_loop_counter = 0;
  							check_channel_routine =0;
  							//ACTUAL_RADIO_STATE = RADIO_RECIEVIED;
  							memset(rx_buffer, 0, sizeof(rx_buffer));
  							memset(RX_RF_Frame_out, 0, sizeof(RX_RF_Frame_out));

  							}
  							//HAL_GPIO_WritePin(PSCK_GPIO_Port, PSCK_Pin, GPIO_PIN_RESET);
  						}
  						else
  						{
  						}
}

void Code_TX_Packet()
{
	uint8_t radio_frame[30];
	memset(radio_frame, 0, sizeof(radio_frame));
	uint16_t radio_frame_crc = 0xFFFF;
	volatile uint8_t loop_counter = 0;

	//adf_init_tx_mode(conf.bitrate, conf.modindex, conf.tx_freq);
//	adf_set_tx_mode();

	//memcpy(tx_buffer, rx_frame, rx_cfg.tx_len + 4);

	radio_frame[0] = SYNC;
	radio_frame[1] = SYNC;
	radio_frame[2] = SYNC;
	radio_frame[3] = STARTB;
	radio_frame[4] = (rx_cfg.dev_no[rx_channel_tab_num]) & 0xFF; //tx_settings.NR & 0xFF;
	radio_frame[5] = (rx_cfg.dev_no[rx_channel_tab_num]) >> 8; //tx_settings.NR >> 8;
	radio_frame[rx_cfg.tx_len + 4] = STOPB;

	tx_buffer[0]++;

	// Add data.
	for (loop_counter = 0; loop_counter < (rx_cfg.tx_len); loop_counter++) { // data
		radio_frame[loop_counter+6] = tx_buffer[loop_counter];
	}

	// Add CRC16.
	radio_frame_crc = 0xFFFF;
	for (int loop_counter = 4; loop_counter < rx_cfg.tx_len + 2; loop_counter++) {
		radio_frame_crc = crc_update(radio_frame_crc, radio_frame[loop_counter]);
	}
	radio_frame[rx_cfg.tx_len + 3] = radio_frame_crc >> 8;
	radio_frame[rx_cfg.tx_len + 2] = radio_frame_crc & 0xFF;			//Dodanie crc do ramki

	memset(tx_data, 0, TX_FRAME_LENGHT);
	memcpy(tx_data,radio_frame,TX_FRAME_LENGHT);
}







