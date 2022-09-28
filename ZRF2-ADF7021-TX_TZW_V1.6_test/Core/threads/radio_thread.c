#include "../ADF7021/adf7021.h"
#include "adf7021_Config.h"

#include <stdint.h>
#include <string.h>
#include "stm32l1xx_hal.h"
#include "../threads/radio_thread.h"
#include "variables.h"
#include "../../config.h"
#include "cmsis_os.h"
#include "main.h"
#include "../Lib/eeprom.h"


extern SPI_HandleTypeDef hspi3;


uint8_t tx_buffer[30];
static uint8_t radio_frame[30];

uint8_t loop_counter = 0;
uint16_t disconnect_counter = 0;
uint8_t disconnect_flag = 0;




volatile uint16_t radio_frame_crc = 0xFFFF;

uint8_t rxBytes;
uint8_t rx_buffer[30] = {0};


extern 	uint8_t power_dbm;

enum {
	RADIO_STATUS_IDLE = 0,
	RADIO_STATUS_TX_MODE = 1,
	RADIO_STATUS_RX_MODE = 2
} local_radio_status = RADIO_STATUS_TX_MODE;



extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart1;
extern struct RF_config conf;
extern uint8_t RX_RF_Frame_out[30];


extern _output_pins Outputs[outputs_count];;

uint8_t temp_55[9] = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55};

void radio_task(void const * argument)
{
	TX_FRAME_LENGHT = tx_cfg.tx_len + 5;
	RX_FRAME_LENGHT = tx_cfg.rx_len + 5;
	uint16_t RX_Delay = 10 + 2*RX_FRAME_LENGHT;
	uint8_t channel = 1;
	uint8_t power = 3;
	vTaskDelay(200/portTICK_RATE_MS);
	adf_reset();
	user_cfg_setup(&channel, &power);
	set_power(power);


	  for(;;)
	  {
		  if(programmode == 0 && !(error_code & CFG_CRC_ERR_BIT))
		  {

			 // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_5);
			 // 	Code_TX_Packet();
			  	SEND_PACKET(temp_55, 9, channel);
			  	REC_PACKET(RX_FRAME_LENGHT, channel,3,0);


				// write R15, set CLK_MUX to enable SPI

			 // test_mode_ON(channel, 0);
			 // osDelay(40);
			 // test_mode_OFF(channel);
			 // osDelay(5);
/*
			  	HAL_GPIO_WritePin( Outputs[9].PORT,Outputs[9].PIN,RESET);
			  	if(tx_cfg.rx_len>0)
			  	{

			  		if(REC_PACKET(RX_FRAME_LENGHT, channel,5,0))
			  		{
			  			if(Decode_RX_Packet())
			  			{
			  				 HAL_GPIO_WritePin( Outputs[9].PORT,Outputs[9].PIN,SET);
			  			}
			  			else
			  			{

			  			}

			  		}
			  		else
			  		{
			  			if(disconnect_counter < 10){disconnect_counter++;}
			  			else
			  			{

			  				disconnect_counter = 0;
			  				memset(rx_frame, 0, sizeof(rx_frame));

			  			}
			  		}
			  	}
*/

		  }
		  else
		  {

			  vTaskDelay(50/portTICK_RATE_MS);
		  }

	  }


}


void Code_TX_Packet()
{


	memset(tx_buffer, 0, tx_cfg.tx_len + 4);
	memcpy(tx_buffer, tx_frame, tx_cfg.tx_len + 4);
	if (xSemaphoreTake(tx_frame_mutex, (portTickType) 10) == pdTRUE) {


	radio_frame[0] = SYNC;
	radio_frame[1] = SYNC;
	radio_frame[2] = SYNC;
	radio_frame[3] = STARTB;
	radio_frame[4] = (tx_cfg.dev_no[tx_settings.NR]) & 0xFF; //tx_settings.NR & 0xFF;
	radio_frame[5] = (tx_cfg.dev_no[tx_settings.NR]) >> 8; //tx_settings.NR >> 8;
	radio_frame[tx_cfg.tx_len + 4] = STOPB;


	// Add data.
	for (loop_counter = 3; loop_counter < (tx_cfg.tx_len); loop_counter++) { // data
		radio_frame[3 + loop_counter] = tx_buffer[loop_counter-3];
	}

	// Add CRC16.
	radio_frame_crc = 0xFFFF;
	for (int loop_counter = 4; loop_counter < tx_cfg.tx_len + 2; loop_counter++) {
		radio_frame_crc = crc_update(radio_frame_crc, radio_frame[loop_counter]);
	}
	radio_frame[tx_cfg.tx_len + 3] = radio_frame_crc >> 8;
	radio_frame[tx_cfg.tx_len + 2] = radio_frame_crc & 0xFF;			//Dodanie crc do ramki


	}
	xSemaphoreGive(tx_frame_mutex);

}


uint16_t rx_number = 0;
uint8_t Decode_RX_Packet()
{
	uint8_t CRC_OK = 0;
	memcpy(rx_buffer,RX_RF_Frame_out,RX_FRAME_LENGHT);
						rxBytes = tx_cfg.rx_len;
						uint16_t radio_frame_crc = 0xFFFF;
  						for (int loop_counter = 0; loop_counter < rxBytes - 2; loop_counter++) {
  							radio_frame_crc = crc_update(radio_frame_crc, rx_buffer[loop_counter]);
  						}

  						if (radio_frame_crc == ((rx_buffer[rxBytes - 1] << 8) | rx_buffer[rxBytes - 2]))		//Je�li crc ok
  						{
  							rx_number = (rx_buffer[1] << 8) | (rx_buffer[0]);
  							if ( rx_number == tx_cfg.dev_no[0] || rx_number == tx_cfg.dev_no[1] || rx_number == tx_cfg.dev_no[2] || rx_number == tx_cfg.dev_no[3] || rx_number == tx_cfg.dev_no[4] || rx_number == tx_cfg.dev_no[5] || rx_number == tx_cfg.dev_no[6] || rx_number == tx_cfg.dev_no[7]){
  							memset(rx_frame, 0, rxBytes - 2);
  							memcpy(rx_frame, &rx_buffer[0], rxBytes - 3);
  							memset(RX_RF_Frame_out, 0, sizeof(RX_RF_Frame_out));
  							//RSSI = adf_readback_rssi();
  							}
  							CRC_OK = 1;
  							return CRC_OK;
  						}
  						else
  						{
  							CRC_OK = 0;
  							return CRC_OK;
  						}
}

void user_cfg_setup(
	uint8_t * const actual_channel,
	uint8_t * const actual_power
) {
	uint16_t cfg_actual_channel = 1;
	uint16_t cfg_actual_power = 3;
	enum {
		CONFIG_CHANGE_NOTHING = 0,
		CONFIG_CHANGE_CHANNEL = 1,
		CONFIG_CHANGE_POWER = 2,
		CONFIG_CHANGE_DONE = 3
	} user_config_change = CONFIG_CHANGE_NOTHING;

	//eeprom_read_variable(CFG_RADIO_CHANNEL_ADDRESS, &cfg_actual_channel);
	//eeprom_read_variable(CFG_RADIO_POWER_ADDRESS, &cfg_actual_power);

	cfg_actual_channel = EEPROM_Read(CFG_RADIO_CHANNEL_ADDRESS_Start + (tx_settings.NR*2));
	cfg_actual_power = 	 EEPROM_Read(CFG_RADIO_POWER_ADDRESS_START+ (tx_settings.NR*2));


	if(cfg_actual_channel == 0){cfg_actual_channel = 1;}
	if(cfg_actual_power == 0){cfg_actual_power = 3;}

	EEPROM_Unlock();


	HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
	HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);

	if ((BB_START == 1) && (BB_STOP == 1)) {

		for(uint8_t timer_change = 0;timer_change < 10;timer_change++)
		{
		setup_flag = 1;


		if ((gpio_port_array[tx_cfg.cfg_sel[0]]->IDR & (1 << gpio_pins_array[tx_cfg.cfg_sel[0]])) == 0) {
			user_config_change = CONFIG_CHANGE_CHANNEL;
			usr_beep(BEEP_GPIO_Port, BEEP_Pin, cfg_actual_channel, 50 / portTICK_RATE_MS, 200 / portTICK_RATE_MS, 0,0);
			break;
		}
		if ((gpio_port_array[tx_cfg.cfg_sel[1]]->IDR & (1 << gpio_pins_array[tx_cfg.cfg_sel[1]])) == 0) {
			user_config_change = CONFIG_CHANGE_POWER;
			usr_beep(BEEP_GPIO_Port, BEEP_Pin, cfg_actual_power, 50 / portTICK_RATE_MS, 200 / portTICK_RATE_MS, 0,0);
			break;
		}

		HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,SET);
		vTaskDelay(1/portTICK_RATE_MS);
		HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);
		vTaskDelay(99/portTICK_RATE_MS);

		}

	}

	while (user_config_change == CONFIG_CHANGE_CHANNEL) {
		HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
		if ((gpio_port_array[tx_cfg.cfg_sel[2]]->IDR & (1 << gpio_pins_array[tx_cfg.cfg_sel[2]])) == 0) {
			cfg_actual_channel += 1U;
			if (cfg_actual_channel > 8U) {
				cfg_actual_channel = 1U;
			}
			usr_beep(BEEP_GPIO_Port, BEEP_Pin, cfg_actual_channel, 50 / portTICK_RATE_MS, 200 / portTICK_RATE_MS, 0,1);
		}
		vTaskDelay(100/portTICK_RATE_MS);
		if (BB_STOP == 0) {
			//eeprom_write_variable(CFG_RADIO_CHANNEL_ADDRESS, cfg_actual_channel);

			EEPROM_Write(CFG_RADIO_CHANNEL_ADDRESS_Start + (tx_settings.NR*2),cfg_actual_channel);
			user_config_change = CONFIG_CHANGE_DONE;
		}
		HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,SET);
		vTaskDelay(2/portTICK_RATE_MS);
		HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);
		vTaskDelay(50/portTICK_RATE_MS);
	}
	while (user_config_change == CONFIG_CHANGE_POWER) {
		HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
		if ((gpio_port_array[tx_cfg.cfg_sel[2]]->IDR & (1 << gpio_pins_array[tx_cfg.cfg_sel[2]])) == 0) {
			cfg_actual_power += 1U;
			if (cfg_actual_power > 3U) {
				cfg_actual_power = 1U;
			}
			usr_beep(BEEP_GPIO_Port, BEEP_Pin, cfg_actual_power, 50 / portTICK_RATE_MS, 200 / portTICK_RATE_MS, 0,1);
		}
		vTaskDelay(100/portTICK_RATE_MS);
		if (BB_STOP == 0) {
			//eeprom_write_variable(CFG_RADIO_POWER_ADDRESS, cfg_actual_power);
			EEPROM_Write(CFG_RADIO_POWER_ADDRESS_START+ (tx_settings.NR*2),cfg_actual_power);
			user_config_change = CONFIG_CHANGE_DONE;
		}
		HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,SET);
		vTaskDelay(2/portTICK_RATE_MS);
		HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);
		vTaskDelay(50/portTICK_RATE_MS);
	}

	setup_flag = 0;


	usr_beep(BEEP_GPIO_Port, BEEP_Pin, 1, 50 / portTICK_RATE_MS, 200 / portTICK_RATE_MS, 0,0);
	*actual_channel = cfg_actual_channel - 1;
	*actual_power = cfg_actual_power;



}

void usr_beep(
	GPIO_TypeDef * buzzer_port,
	const uint32_t buzzer_pin,
	const uint8_t beep_no,
	const uint32_t beep_time,
	const uint32_t idle_time,
	const uint8_t off_state,
	const uint8_t led
) {

	HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);
	HAL_GPIO_WritePin(LEDR_GPIO_Port,LEDR_Pin,RESET);
	uint8_t loop_counter = 0;
	for (loop_counter = 0; loop_counter < beep_no; loop_counter++) {
		if (off_state == 0) {
			if(led>0){HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,SET);}
			 HAL_GPIO_WritePin(buzzer_port, buzzer_pin,SET);
		}
		else {
			if(led>0){HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);}
			HAL_GPIO_WritePin(buzzer_port, buzzer_pin,RESET);
		}
		vTaskDelay(beep_time);
		if (off_state == 0) {
			if(led>0){HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,RESET);}
			HAL_GPIO_WritePin(buzzer_port, buzzer_pin,RESET);
		}
		else {
			if(led>0){HAL_GPIO_WritePin(LEDG_GPIO_Port,LEDG_Pin,SET);}
			HAL_GPIO_WritePin(buzzer_port, buzzer_pin,SET);
		}
		vTaskDelay(idle_time);
	}
}





uint16_t crc_update(uint16_t crc,uint8_t data)
{
    data ^= (uint8_t) (crc & 0xFF);
    data ^= data << 4;
    return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}
