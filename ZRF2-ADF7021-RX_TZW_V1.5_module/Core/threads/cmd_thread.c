

#include <stdint.h>
#include <string.h>
#include <stdio.h>

//#include "../lib/flash.h"
#include "stm32l1xx_hal.h"
#include "../lib/xprintf.h"
#include "../threads/radio_thread.h"
#include "../threads/io_ctrl_thread.h"
#include "../threads/cmd_thread.h"
#include "../ADF7021/adf7021.h"
#include "config.h"
#include "variables.h"
#include "cmsis_os.h"

#include "main.h"

#include "../Lib/eeprom.h"

extern osThreadId radio_threadHandle;
extern osThreadId io_ctrl_threadHandle;
//extern IWDG_HandleTypeDef hiwdg;

#define USR_ASSERT_ERROR_MSG_ADDRESS 2
#define cfg_buff_adress 4

uint8_t cfg_buffer[32];
uint8_t buffer_8[20];
uint16_t  buffer_16[10];
extern uint8_t tmp_frame[22];
static uint16_t eeprom_byte_counter =0;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;



volatile uint8_t received[1];
uint8_t RF_received[1];
uint8_t RX_cnt = 0;



BaseType_t xHigherPriorityTaskWoken;
portBASE_TYPE queue_status_isr = pdFALSE;
portBASE_TYPE RF_queue_status_isr = pdFALSE;







extern uint8_t analog_out[8];

extern uint8_t RX_RF_Frame_tmp[45];


void cmd_task(void const * argument) {

	HAL_FLASHEx_DATAEEPROM_Unlock();

	uint8_t queue_first_byte = 0;
	uint8_t queue_first_byte_tx = 0;

	portBASE_TYPE queue_status = pdFALSE;
	portBASE_TYPE rx_queue_status = pdFALSE;

	char cmd_table[50];
	char RF_table[128];
	uint8_t cmd_item_counter = 0;




	memset(cmd_table, 0, 50);
	memset(RF_table, 0, 128);


	HAL_UART_Receive_IT(&huart1, &received[1], 1);

	//HAL_UARTEx_ReceiveToIdle_DMA(&huart3, RX_RF_Frame_tmp, RADIO_FRAME_LENGHT);
	//HAL_UART_Receive_IT(&huart3, &RF_received[0], 1);

//HAL_UART_Receive_IT(&huart3, RX_RF_Frame_tmp, RADIO_FRAME_LENGHT+1);

	//__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	//HAL_NVIC_SetPriority(USART1_IRQn, 10, 0);
	//HAL_NVIC_EnableIRQ(USART1_IRQn);



	//	HAL_UART_Receive_DMA(&huart3, RX_RF_Frame_out, RADIO_FRAME_LENGHT);

	//HAL_UART_Transmit_DMA(&huart3, &radio_frame[0], rx_cfg.rx_len +5);

	  for (;;) {
/*
		  rx_queue_status = xQueueReceive(RF_RX_queue, &queue_first_byte_RF, 1);

			if (RF_queue_status_isr == pdPASS) {

				RF_table[cmd_item_counter_RF] = (char)queue_first_byte_RF;
				cmd_item_counter_RF++;
				if(cmd_item_counter_RF > 11)
				{
					if(RF_table [cmd_item_counter_RF - 2] == 0x55 && RF_table [cmd_item_counter_RF - 1] == 0x55 &&RF_table [cmd_item_counter_RF ] == 0x55)
					{
						cmd_item_counter_RF = 0;
					}
				}

			}

*/






/*
			if(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) && Radio_TX_Mode == RADIO_TX_START &&  radio_status == 1)
			{

				adf_set_tx_mode();
			    HAL_UART_Transmit(&huart3, &radio_frame[0], rx_cfg.rx_len +5,25);
			    adf_set_rx_mode();
			    HAL_UART_Receive_IT(&huart3, &RF_received[0], 1);


				Radio_TX_Mode = RADIO_TX_END;

			}
*/

/*
		  if(Radio_TX_Mode == RADIO_TX_START)
		  {
				adf_set_tx_mode();
				HAL_UART_Transmit_IT(&huart3, &radio_frame[0], rx_cfg.rx_len +5);
				adf_set_rx_mode();
				Radio_TX_Mode = RADIO_TX_END;
		  }
*/


		  rx_queue_status = xQueueReceive(serial_rx_queue, &queue_first_byte, 1);


			if (rx_queue_status == pdPASS) {

				cmd_table[cmd_item_counter] = (char)queue_first_byte;
				switch (queue_first_byte) {
				case 0x0A:
					cmd_item_counter = 0U;
					cmd_execute(cmd_table);
					break;
				case 0x02:
					cmd_item_counter = 0U;
					break;
				default:
					if (cmd_item_counter < 50U) {
						cmd_item_counter++;
					}
					else {
						cmd_item_counter = 0U;
					}
					break;
				}
			}
			else
			{
				osDelay(1);
			}

			  if((USART1->SR & USART_SR_RXNE) == 0)
			    {


				queue_status = xQueueReceive(serial_tx_queue, &queue_first_byte_tx, 1);
				if (queue_status == pdPASS) {

					HAL_UART_Transmit(&huart1,&queue_first_byte_tx,1,2);
					__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);


				}
				else {

				}
			  }

			taskYIELD();

	  }

}



void cmd_execute(char *cmd) {
	enum {
		ACTION_DO_NOTHING = 0,
		ACTION_GET_FRAME = 1,
		ACTION_GET_VERSION = 2,
		ACTION_GET_NUMBER = 3,
		ACTION_GET_STATUS = 4,
		ACTION_GET_CRC = 5,
		ACTION_GET_ANALOG = 6,
		ACTION_CFG_DUMP = 7,
		ACTION_GET_ASSERT = 8,
		ACTION_CLEAR_ASSERT = 9,
		ACTION_CFG_SET = 20,
		ACTION_CFG_GET = 21,
		ACTION_CFG_SAVE = 22,
		ACTION_CFG_LENGTH = 23,
		ACTION_GET_RSSI = 24,
		ACTION_DEV_RESET = 30,
		ACTION_DEV_PRG_START = 31
	} action = ACTION_DO_NOTHING;
	uint16_t loop_counter = 0;
	uint8_t data_length = 0;
	uint8_t temp[] = {0, 0, 0, 0, 0};

	uint16_t cfg_counter = 0U;
	static uint16_t cfg_length = 0U;
	uint16_t cfg_crc = 0xFFFF;
	uint16_t byte;


	if (strncmp("gf", cmd, 2) == 0) action = ACTION_GET_FRAME;
	if (strncmp("gv", cmd, 2) == 0) action = ACTION_GET_VERSION;
	if (strncmp("gd", cmd, 2) == 0) action = ACTION_GET_NUMBER;
	if (strncmp("gs", cmd, 2) == 0) action = ACTION_GET_STATUS;
	if (strncmp("gc", cmd, 2) == 0) action = ACTION_GET_CRC;
	if (strncmp("ga", cmd, 2) == 0) action = ACTION_GET_ASSERT;
	if (strncmp("cd", cmd, 2) == 0) action = ACTION_CFG_DUMP;
	if (strncmp("cs", cmd, 2) == 0) action = ACTION_CFG_SET;
	if (strncmp("cw", cmd, 2) == 0) action = ACTION_CFG_SAVE;
	if (strncmp("cg", cmd, 2) == 0) action = ACTION_CFG_GET;
	if (strncmp("cl", cmd, 2) == 0) action = ACTION_CFG_LENGTH;
	if (strncmp("gr", cmd, 2) == 0) action = ACTION_GET_RSSI;
	if (strncmp("dr", cmd, 2) == 0) action = ACTION_DEV_RESET;
	if (strncmp("ds", cmd, 2) == 0) action = ACTION_DEV_PRG_START;
	if (strncmp("ga", cmd, 2) == 0) action = ACTION_GET_ANALOG;


	switch (action) {

	case ACTION_GET_ANALOG:

		xsprintf(
					system_frame_str,
					"%2X%2X%2X%2X%2X%2X%2X%2X",
					analog_out[0],
					analog_out[1],
					analog_out[2],
					analog_out[3],
					analog_out[4],
					analog_out[5],
					analog_out[6],
					analog_out[7]

				);


				string_zero_fill(system_frame_str);
				serial_send_string(system_frame_str);
				serial_send_string("Z");
				serial_send_string("\n");
				vTaskDelay(1/portTICK_RATE_MS);
		break;

	case ACTION_GET_FRAME:
		memset(tmp_frame,0,sizeof(tmp_frame));
		//memcpy(tmp_frame, &RX_RF_Frame_out[3],RADIO_FRAME_LENGHT-9);

		xsprintf(
					system_frame_str,
					"%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X",

					tmp_frame[0],
					tmp_frame[1],
					tmp_frame[2],
					tmp_frame[3],
					tmp_frame[4],
					tmp_frame[5],
					tmp_frame[6],
					tmp_frame[7],
					tmp_frame[8],
					tmp_frame[9],
					tmp_frame[10],
					tmp_frame[11],
					tmp_frame[12],
					tmp_frame[13],
					tmp_frame[14],
					tmp_frame[15],
					tmp_frame[16],
					tmp_frame[17],
					tmp_frame[18],
					tmp_frame[19],
					tmp_frame[20],
					tmp_frame[21]
				);


				string_zero_fill(system_frame_str);
				serial_send_string(system_frame_str);
				serial_send_string("Z");
				serial_send_string("\n");
				vTaskDelay(1/portTICK_RATE_MS);
		break;

	case ACTION_GET_VERSION:
		string_zero_fill(system_version_str);
		serial_send_string(system_version_str);

		xsprintf(debug_str,	"     num: %5u\n", rx_cfg.dev_no[0]);

		serial_send_string(debug_str);

		break;
	case ACTION_GET_NUMBER:

		xsprintf(debug_str,	"number=%5u\n", rx_cfg.dev_no[0]);
		//xsprintf(debug_str,	"number=%5u\n", RX_cnt);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);


/*
			xsprintf(system_dev_no_str, "radio_frame_len=%2u,readed_frame_len=%2u", Radio_frame_lenght,Frm_cnt);
			string_zero_fill(system_dev_no_str);
			serial_send_string(system_dev_no_str);

			serial_send_string("\r\n");
			serial_send_string("CYFROWE");
			serial_send_string("\r\n");


			serial_send_string("\r\n");
			serial_send_string("Analogowe");
			serial_send_string("\r\n");
			for(uint8_t c = 0; c < rx_cfg.offset; c++)
			{
				xsprintf(system_dev_no_str, "%2X,", rx_frame[c]);
				string_zero_fill(system_dev_no_str);
				serial_send_string(system_dev_no_str);
			}
*/


			vTaskDelay(1/portTICK_RATE_MS);
		serial_send_string("\r\n");
		break;
	case ACTION_GET_STATUS:

		xsprintf(debug_str,	"number=%5u", rx_cfg.dev_no[0]);
						string_zero_fill(debug_str);
						serial_send_string(debug_str);
		xsprintf(debug_str,	"rx_len=%2u", rx_cfg.rx_len);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
		xsprintf(debug_str,	"offset=%2u", rx_cfg.offset);
						string_zero_fill(debug_str);
						serial_send_string(debug_str);
  			serial_send_string("N");
  			serial_send_string("\n");

/*
		xsprintf(debug_str,	"STAN=%02X", (sate_arr[0] >> 1));
		string_zero_fill(debug_str);
		serial_send_string(debug_str);
		serial_send_string("\r\n");

		xsprintf(debug_str,	"ISR=%02X:%02X:%02X:%02X", ISR[0],ISR[1],ISR[2],ISR[3]);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);
		serial_send_string("\r\n");
*/







  			//vTaskDelay(1/portTICK_RATE_MS);
		break;
	case ACTION_GET_CRC:
		cfg_crc = 0xFFFF;
		for (loop_counter = 0U; loop_counter < cfg_length - 2; loop_counter++) {
			byte = *(__IO uint16_t*) (DATA_EEPROM_START_ADDR + loop_counter);
			cfg_crc = crc16_update(cfg_crc, byte);

		}
		//siprintf(debug_str, "%02x%02x", rx_cfg.fb_crc >> 8, rx_cfg.fb_crc & 0xFF);
		xsprintf(debug_str, "%02x%02x", cfg_crc & 0xFF, cfg_crc >> 8);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);
		serial_send_string("\n");
		break;

	case ACTION_CFG_DUMP:
		xsprintf(debug_str,	"fb_len=0x%4X", rx_cfg.fb_len);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);
		xsprintf(debug_str,	"cfg_ver_conf=0x%2X,_cfg_ver_flash=0x%2X", rx_cfg.cfg_ver,CFG_VERSION);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);
		xsprintf(
			debug_str,
			"fr_rx=[%2u,%2u,%2u,%2u,%2u,%2u,%2u,%2u]",
			rx_cfg.fr_rx[0],
			rx_cfg.fr_rx[1],
			rx_cfg.fr_rx[2],
			rx_cfg.fr_rx[3],
			rx_cfg.fr_rx[4],
			rx_cfg.fr_rx[5],
			rx_cfg.fr_rx[6],
			rx_cfg.fr_rx[7]
		);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);

		xsprintf(
			debug_str,
			"tx_len=%2u",
			rx_cfg.tx_len

		);

		xsprintf(
			debug_str,
			"dev=[%u,%u,%u,%u,%u,%u,%u,%u]",
			rx_cfg.dev_no[0],
			rx_cfg.dev_no[1],
			rx_cfg.dev_no[2],
			rx_cfg.dev_no[3],
			rx_cfg.dev_no[4],
			rx_cfg.dev_no[5],
			rx_cfg.dev_no[6],
			rx_cfg.dev_no[7]
		);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);

		xsprintf(
			debug_str,
			"rx_len=%2u",
			rx_cfg.rx_len

		);

		xsprintf(debug_str, "move_chk=%u", rx_cfg.move_chk);
		serial_send_string(debug_str);

		serial_send_string("\r\n");

		xsprintf(
			debug_str,
			"spi=[%3u,%3u,%3u,%3u]",
			rx_cfg.spi_cfg[0],
			rx_cfg.spi_cfg[2],
			rx_cfg.spi_cfg[4],
			rx_cfg.spi_cfg[6],
			rx_cfg.spi_cfg[8]

		);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);




		serial_send_string("\r\n");

		xsprintf(
			debug_str,
			"toggle=[%4X,%4X,%4X,%4X]",
			rx_cfg.toggle[0],
			rx_cfg.toggle[1],
			rx_cfg.toggle[2],
			rx_cfg.toggle[3]

		);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);

		serial_send_string("\r\n");

		for(uint8_t c = 0; c < 7 ; c++)
		{
			xsprintf(debug_str, "____ANALOG=%2X,An0=%2X,An1=%2X,N=%2X,S=%2X____",c, rx_cfg.analog[c].an_0,rx_cfg.analog[c].an_1,rx_cfg.analog[c].n,rx_cfg.analog[c].size);
			serial_send_string(debug_str);
			serial_send_string("\r\n");
		}
		serial_send_string("\r\n");

		xsprintf(
			debug_str,
			"tval_no=[%4X,%4X,%4X,%4X,%4X,%4X,%4X,%4X,%4X,%4X]",
			rx_cfg.tval_tab[0],
			rx_cfg.tval_tab[1],
			rx_cfg.tval_tab[2],
			rx_cfg.tval_tab[3],
			rx_cfg.tval_tab[4],
			rx_cfg.tval_tab[5],
			rx_cfg.tval_tab[6],
			rx_cfg.tval_tab[7],
			rx_cfg.tval_tab[8],
			rx_cfg.tval_tab[9]

		);
		serial_send_string(debug_str);
		serial_send_string("\r\n");


		xsprintf(debug_str, "an_bit=%u", rx_cfg.an_bit);
		serial_send_string(debug_str);

		xsprintf(debug_str, "bit_stop=%u", rx_cfg.bit_stop);
		serial_send_string(debug_str);
		xsprintf(debug_str, "offset=%u", rx_cfg.offset);
		serial_send_string(debug_str);
		vTaskDelay(1/portTICK_RATE_MS);
		serial_send_string("\n");
		break;
	case ACTION_GET_ASSERT:
		for (loop_counter = 0; loop_counter < 100U; loop_counter++) {
			//eeprom_read_variable(USR_ASSERT_ERROR_MSG_ADDRESS + loop_counter, (uint16_t*)&debug_str[loop_counter]);
		}
		if (debug_str[0] == 0) {
			serial_send_string("No asserts.");
		}
		else {
			serial_send_string(debug_str);
		}
		break;
	case ACTION_CLEAR_ASSERT:
		for (loop_counter = 0; loop_counter < 100U; loop_counter++) {
			//eeprom_write_variable(USR_ASSERT_ERROR_MSG_ADDRESS + loop_counter, 0);
		}
		break;
	case ACTION_CFG_SET:
		ascii_to_uint(cmd[2], cmd[3], &temp[0]);
		ascii_to_uint(cmd[4], cmd[5], &temp[1]);
		cfg_counter = (temp[0] << 8) | temp[1];			//Numer strony danych
		ascii_to_uint(cmd[6], cmd[7], &data_length); //ilosc bajtow w ramce
		for (loop_counter = 0; loop_counter < data_length; loop_counter++){
			ascii_to_uint(cmd[(loop_counter * 2) + 8], cmd[(loop_counter * 2) + 9], &temp[0]);
			//buffer_8[loop_counter] = 0;
			//buffer_8[loop_counter] = temp[0];

			//writeToEEPROM(DATA_EEPROM_START_ADDR + 2 +cfg_counter,temp[0]);


			eeprom_byte_counter = (cfg_counter) + loop_counter;

			//FLASH_DATAEEPROM_FastProgramByte(DATA_EEPROM_START_ADDR + 2 +eeprom_byte_counter, (uint8_t) temp[0]);

			*(__IO uint8_t *)(DATA_EEPROM_START_ADDR + 2 +eeprom_byte_counter) = temp[0];

			vTaskDelay(1/portTICK_RATE_MS);
	      // HAL_FLASHEx_DATAEEPROM_Erase (FLASH_TYPEERASEDATA_BYTE, DATA_EEPROM_START_ADDR + 2 +eeprom_byte_counter);
	       //for(volatile uint32_t i=0;i<0x1F;i++);
	      // HAL_FLASHEx_DATAEEPROM_Program (FLASH_TYPEPROGRAMDATA_BYTE, DATA_EEPROM_START_ADDR + 2 + eeprom_byte_counter, temp[0]);
		}
		serial_send_string("r");
		serial_send_string("\n");
		break;
	case ACTION_CFG_GET:


		for (loop_counter = 0; loop_counter < 4; loop_counter++) {

			byte = *(__IO uint16_t*) (&rx_cfg.toggle[0] + loop_counter); //Zmiana
			xQueueSend(serial_tx_queue, (void*)&byte, 5 / portTICK_RATE_MS);
		}

		break;
	case ACTION_CFG_SAVE:
		vTaskDelay(1 / portTICK_RATE_MS);


		serial_send_string("e");
		serial_send_string("\n");

		break;
	case ACTION_CFG_LENGTH:

		ascii_to_uint(cmd[4], cmd[5], &temp[0]);
		ascii_to_uint(cmd[2], cmd[3], &temp[1]);
		cfg_length = ((temp[0] << 8) | temp[1]) + 2;
		cfg_counter = 0;
		uint16_t len_cfg[1];
		len_cfg[0]= (uint16_t)((temp[0] << 8) | temp[1]);
		//usr_cfg_write_to_flash_buffer(len_cfg,1,0);
	       HAL_FLASHEx_DATAEEPROM_Erase (FLASH_TYPEERASEDATA_BYTE, DATA_EEPROM_START_ADDR);
	       HAL_FLASHEx_DATAEEPROM_Erase (FLASH_TYPEERASEDATA_BYTE, DATA_EEPROM_START_ADDR+1);
	       HAL_FLASHEx_DATAEEPROM_Program (FLASH_TYPEPROGRAMDATA_BYTE, DATA_EEPROM_START_ADDR, temp[1]);
	       HAL_FLASHEx_DATAEEPROM_Program (FLASH_TYPEPROGRAMDATA_BYTE, DATA_EEPROM_START_ADDR+1, temp[0]);
		serial_send_string("l");
		serial_send_string("\n");
		break;
	case ACTION_GET_RSSI:
		xsprintf(debug_str,	"%4d", RSSI);

		//continous_rssi = 1;
		RSSI = 0;
		//string_zero_fill(debug_str);
		serial_send_string(debug_str);
		serial_send_string("R\n");
		break;


	case ACTION_DEV_PRG_START:
		programmode = 1;

		system_errors.cfg_crc = 1;

		osThreadSuspend(radio_threadHandle);
		osThreadSuspend(io_ctrl_threadHandle);

		vTaskDelay(100 / portTICK_RATE_MS);
		//flash_erase_page(CFG_FlASH_PAGE_ADDRESS);
		//flash_erase_page(CFG_FlASH_PAGE_ADDRESS+1024);
		//flash_erase_page(CFG_FlASH_PAGE_ADDRESS+2048);


		serial_send_string("r");
		serial_send_string("\n");

	//	while(1);
		break;

	case ACTION_DEV_RESET:

		NVIC_SystemReset();
		programmode = 0;
		serial_send_string("\n");

	//	while(1);
		break;
	case ACTION_DO_NOTHING:
	default:
		serial_send_string("Invalid command.");
		serial_send_string("\n");
		break;
	}
}



#define STM32L152_HighDensitySysMemLocation (0x1FF00000)
extern ADC_HandleTypeDef hadc;
extern SPI_HandleTypeDef hspi2;
void JumpToBootloader (void)
{
    typedef void (*JumpFct)(void);
    // Make sure jump location is held in register
    register JumpFct SysMemBootJump asm ("r2");


    HAL_ADC_DeInit(&hadc);
    HAL_UART_DeInit(&huart1);

    HAL_SPI_DeInit(&hspi2);
    __HAL_RCC_TIM2_CLK_DISABLE();

    SCB->VTOR = 0;
    // Which one should I use?
    //SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET;

    HAL_MspDeInit();
    HAL_RCC_DeInit();

    // Step: Disable systick timer and reset it to default values
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    // Disable all interrupts
    __disable_irq();

    // Execute in order, just to be safe
    __DSB();

    // Step: Remap system memory to address 0x0000 0000 in address space
    __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();

    // Execute in order, wait for all instructions up to this point to exit the pipeline
    __DSB();
    __ISB();

    // Step: Set jump memory location for system memory
    // Use address with 4 bytes offset which specifies jump location where program starts
    // See AN2606 document
    SysMemBootJump = (JumpFct) (*((volatile uint32_t *) ((STM32L152_HighDensitySysMemLocation + 4))));

    // Step: Set main stack pointer.
    // This step must be done last otherwise local variables in this function
    // don't have proper value since stack pointer is located on different position
    // Set direct address location which specifies stack pointer in SRAM location
    __set_MSP(*(volatile uint32_t*) STM32L152_HighDensitySysMemLocation);


    // Step: Actually call our function to jump to set location
    // This will start system memory execution
    SysMemBootJump();

    while(1);
}




void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)  // change USART instance
    {

    }




}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)
    {
    	//received[0]= USART1->DR;
    	queue_status_isr = xQueueSendFromISR( serial_rx_queue, &received, &xHigherPriorityTaskWoken );
    	HAL_UART_Receive_IT(&huart1, &received[0], 1);

    }



    if (huart->Instance == USART3)
    {}

}



void serial_send_string(char *str)
{

    uint8_t i = '\n';
    for (i = 0; ; i++) {

        if ((str[i] == '\0')) break;
        xQueueSend(serial_tx_queue, (void*)&str[i], ( TickType_t ) 5);


    }


}




void string_zero_fill(char *str) {
	uint8_t loop_counter = 0U;
	for (loop_counter = 0U; ; loop_counter++) {
		if (str[loop_counter] == '\0') {
			break;
		}
		else {
			if (str[loop_counter] == ' ') {
				str[loop_counter] = '0';
			}
		}
	}
}

uint8_t uint_to_ascii(
	uint8_t const uint,
	uint8_t * const ascii_high,
	uint8_t * const ascii_low
)
{
	*ascii_high = return_ASCII(uint / 16);
	*ascii_low = return_ASCII(uint % 16);
	return TRANSFER_FS_NO_ERRORS;
}

uint8_t ascii_to_uint(
	uint8_t const ascii_high,
	uint8_t const ascii_low,
	uint8_t * const uint
)
{
	*uint = return_uint(ascii_high) * 16;
	*uint += return_uint(ascii_low);
	return TRANSFER_FS_NO_ERRORS;
}

inline uint8_t return_ASCII(uint8_t num)
{
	if (num < 10) return (char)(num + 0x30);
	else return (char)(num + 0x37);
}

inline uint8_t return_uint(
	uint8_t ascii
){
	if (ascii > 0x3A) return (uint8_t)(ascii - 0x37);
	else return (uint8_t)(ascii - 0x30);
}
