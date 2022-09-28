
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "stm32l1xx_hal.h"
#include "../lib/xprintf.h"
#include "../threads/radio_thread.h"
#include "../threads/io_ctrl_thread.h"

#include "../threads/cmd_thread.h"
//#include "../assert.hpp"
#include "../../config.h"
#include "variables.h"
#include "cmsis_os.h"
#include "../lib/eeprom.h"

//#include "../stm32f10x.h"
#include "main.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern osThreadId radio_threadHandle;
extern osThreadId io_ctrl_threadHandle;
extern TIM_HandleTypeDef htim11;


uint8_t buffer_txe[160];


extern uint8_t inputs_array[128];
extern uint8_t sbi[22];
extern uint8_t tmp_tab[24];

portBASE_TYPE queue_status = pdFALSE;

static uint16_t eeprom_byte_counter =0;
static uint8_t received[1];
static uint8_t RF_received[2];
volatile uint16_t rx_timeout = 0;


uint8_t RX_RF_Frame_out[30];
const uint8_t MAX_search_rx = 45;
volatile uint8_t RX_cnt = 0;
uint8_t RX_RF_Frame_tmp[45];


void cmd_task(void const * argument) {
	HAL_FLASHEx_DATAEEPROM_Unlock();
	uint8_t queue_first_byte = 0;
	uint8_t queue_first_byte_tx = 0;
	portBASE_TYPE queue_status = pdFALSE;
	portBASE_TYPE rx_queue_status = pdFALSE;

	char cmd_table[50];
	uint8_t cmd_item_counter = 0;

	char RF_table[128];
	uint8_t cmd_item_counter_RF = 0;



	memset(cmd_table, 0, 50);
	memset(RF_table, 0, 128);

	RX_RF_Frame_tmp[0] = 0x55;
	HAL_UART_Receive_IT(&huart1, &received[1], 1);


	//__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	//HAL_NVIC_SetPriority(USART1_IRQn, 10, 0);
	//HAL_NVIC_EnableIRQ(USART1_IRQn);




	  for (;;) {




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
			{}

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
		ACTION_GET_ADC = 6,
		ACTION_CFG_DUMP = 7,
		ACTION_GET_ASSERT = 8,
		ACTION_CLEAR_ASSERT = 9,
		ACTION_CFG_SET = 20,
		ACTION_CFG_GET = 21,
		ACTION_CFG_SAVE = 22,
		ACTION_CFG_LENGTH = 23,
		ACTION_DEV_RESET = 30,
		ACTION_DEV_PRG_START = 31,
		ACTION_DEV_RADIO_STATE = 32,
		ACTION_DEV_RADIO_SET_PA = 33,
		ACTION_DEV_RADIO_SET_PN9 = 34,
		ACTION_DEV_GO_BOOT = 35
	} action = ACTION_DO_NOTHING;

	uint16_t loop_counter = 0;
	uint8_t data_length = 0;
	uint8_t tmp_frame[50];
	static  uint8_t temp[] = {0, 0, 0, 0, 0};
	uint16_t cfg_counter = 0U;
	static  uint16_t cfg_length;
	uint16_t cfg_crc = 0xFFFF;
	uint16_t byte;



	//uint8_t buffer_8[20];
	//uint16_t  buffer_16[8];


	char debug_str[150];



	if (strncmp("gf", cmd, 2) == 0) action = ACTION_GET_FRAME;
	if (strncmp("gv", cmd, 2) == 0) action = ACTION_GET_VERSION;
	if (strncmp("gd", cmd, 2) == 0) action = ACTION_GET_NUMBER;
	if (strncmp("gs", cmd, 2) == 0) action = ACTION_GET_STATUS;
	if (strncmp("gc", cmd, 2) == 0) action = ACTION_GET_CRC;
	if (strncmp("ad", cmd, 2) == 0) action = ACTION_GET_ADC;
	if (strncmp("ga", cmd, 2) == 0) action = ACTION_GET_ASSERT;
	if (strncmp("cd", cmd, 2) == 0) action = ACTION_CFG_DUMP;
	if (strncmp("cs", cmd, 2) == 0) action = ACTION_CFG_SET;
	if (strncmp("cw", cmd, 2) == 0) action = ACTION_CFG_SAVE;
	if (strncmp("cg", cmd, 2) == 0) action = ACTION_CFG_GET;
	if (strncmp("cl", cmd, 2) == 0) action = ACTION_CFG_LENGTH;
	if (strncmp("dr", cmd, 2) == 0) action = ACTION_DEV_RESET;
	if (strncmp("ds", cmd, 2) == 0) action = ACTION_DEV_PRG_START;
	if (strncmp("rs", cmd, 2) == 0) action = ACTION_DEV_RADIO_STATE;
	if (strncmp("sp", cmd, 2) == 0) action = ACTION_DEV_RADIO_SET_PA;
	if (strncmp("pn", cmd, 2) == 0) action = ACTION_DEV_RADIO_SET_PN9;
	if (strncmp("gb", cmd, 2) == 0) action = ACTION_DEV_GO_BOOT;



	switch (action) {
	case ACTION_GET_FRAME:

		memcpy(tmp_frame, &tx_frame[1], 21);

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
				vTaskDelay(1 / portTICK_RATE_MS);

		break;

	case ACTION_DEV_RADIO_STATE:
	//	xsprintf(debug_str,	"_bat=%4u", bat_voltage);
	//	string_zero_fill(debug_str);
	//	serial_send_string(debug_str);
	//	serial_send_string("\r\n");

		for(int c = 0; c < 64; c++)
		{
			xsprintf(debug_str,"%2U,",inputs_array[c]);
			serial_send_string(debug_str);
		}


		serial_send_string("\n");


	break;

	case ACTION_GET_VERSION:
		//xsprintf(debug_str,"%u,%u,%u,%u,%u,%u,%u,",xIrqStatus.IRQ_BOR,xIrqStatus.IRQ_CRC_ERROR,xIrqStatus.IRQ_LOCK,xIrqStatus.IRQ_LOW_BATT_LVL,
		//		xIrqStatus.IRQ_POR,xIrqStatus.IRQ_READY,xIrqStatus.IRQ_TX_FIFO_ERROR);

		xsprintf(debug_str, "%u", tx_cfg.cfg_ver);
		serial_send_string(debug_str);

		//HAL_UART_Transmit(&huart1,&xIrqStatus,sizeof(S2LPIrqs),100);

		serial_send_string("\n");

		break;
	case ACTION_GET_NUMBER:
		xsprintf(system_dev_no_str, "%5u", tx_cfg.dev_no[tx_settings.NR]);
				string_zero_fill(system_dev_no_str);
				serial_send_string(system_dev_no_str);
				serial_send_string("\n");
				vTaskDelay(1 / portTICK_RATE_MS);


		break;
	case ACTION_GET_STATUS:

		xsprintf(debug_str,	"number=%4u", tx_cfg.dev_no[0]);
						string_zero_fill(debug_str);
						serial_send_string(debug_str);
		xsprintf(debug_str,	"tx_len=%2u", tx_cfg.tx_len);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
		xsprintf(debug_str,	"offset=%2u", tx_cfg.byte_offset);
						string_zero_fill(debug_str);
						serial_send_string(debug_str);
  			serial_send_string("N");
  			serial_send_string("\n");
  			vTaskDelay(1 / portTICK_RATE_MS);

/*
				xsprintf(debug_str,	"STAN=%02X", (sate_arr[0] >> 1));
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
				serial_send_string("\r\n");

		//		xsprintf(debug_str,	"ISR=%02X:%02X:%02X:%02X:%u", ISR[0],ISR[1],ISR[2],ISR[3],ISR[4]);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
				serial_send_string("\r\n");
*/
		break;
	case ACTION_GET_CRC:
		cfg_crc = 0xFFFF;
		for (loop_counter = 0U; loop_counter < cfg_length - 2; loop_counter++) {
			byte = *(__IO uint16_t*) (DATA_EEPROM_START_ADDR + loop_counter);
			cfg_crc = crc16_update(cfg_crc, byte);
			buffer_txe[loop_counter] = byte;
		}
		//siprintf(debug_str, "%02x%02x", rx_cfg.fb_crc >> 8, rx_cfg.fb_crc & 0xFF);
		xsprintf(debug_str, "%02x%02x", cfg_crc & 0xFF, cfg_crc >> 8);
		string_zero_fill(debug_str);
		serial_send_string(debug_str);
		serial_send_string("\n");
		break;
	case ACTION_GET_ADC:
		for(uint8_t c = 0; c < 8; c++)
		{
		siprintf(debug_str, "_%4u\n", system_adc_values[c]);
		string_zero_fill(debug_str);
				serial_send_string(debug_str);
		}
		serial_send_string("\n");
				break;
	case ACTION_CFG_DUMP:
		xsprintf(debug_str,	"_fb_len=0x%4X", tx_cfg.fb_len);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_cfg_ver=0x%4X", tx_cfg.cfg_ver);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_off_time1=0x%4X", tx_cfg.off_time1);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_off_time2=0x%4X", tx_cfg.off_time2);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_off_time3=0x%4X", tx_cfg.off_time3);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_ir1=0x%4X", tx_cfg.ired1);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_ir2=0x%4X", tx_cfg.ired2);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);





				xsprintf(
					debug_str,
					"_fr_rx=[%2u,%2u,%2u,%2u,%2u,%2u,%2u,%2u]",
					tx_cfg.fr_tx[0],
					tx_cfg.fr_tx[1],
					tx_cfg.fr_tx[2],
					tx_cfg.fr_tx[3],
					tx_cfg.fr_tx[4],
					tx_cfg.fr_tx[5],
					tx_cfg.fr_tx[6],
					tx_cfg.fr_tx[7]
				);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
				xsprintf(
					debug_str,
					" dev_no=[%u,%u,%u,%u,%u,%u,%u,%u]",
					tx_cfg.dev_no[0],
					tx_cfg.dev_no[1],
					tx_cfg.dev_no[2],
					tx_cfg.dev_no[3],
					tx_cfg.dev_no[4],
					tx_cfg.dev_no[5],
					tx_cfg.dev_no[6],
					tx_cfg.dev_no[7]
				);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(
					debug_str,
					"_cfg_no=[0x%2X,0x%2X,0x%2X]",
					tx_cfg.num_sel[0],
					tx_cfg.num_sel[1],
					tx_cfg.num_sel[2]
				);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);


				xsprintf(
					debug_str,
					"_sel_no=[0x%2X,0x%2X,0x%2X]",
					tx_cfg.cfg_sel[0],
					tx_cfg.cfg_sel[1],
					tx_cfg.cfg_sel[2]
				);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);



				xsprintf(debug_str,	"_txlen=%2u", tx_cfg.tx_len);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str, "crc_=0x%2X", tx_cfg.crc_type);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
/*
				xsprintf(debug_str,	"_spi=%2u", tx_cfg.spi_no);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);
*/
				xsprintf(
					debug_str,
					"_spi_no=[0x%1X,0x%1X,0x%1X,0x%1X,0x%1X,0x%1X,0x%1X,0x%1X]",
					tx_cfg.spi_cfg[0],
					tx_cfg.spi_cfg[1],
					tx_cfg.spi_cfg[2],
					tx_cfg.spi_cfg[3],
					tx_cfg.spi_cfg[4],
					tx_cfg.spi_cfg[5],
					tx_cfg.spi_cfg[6],
					tx_cfg.spi_cfg[7]
				);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				xsprintf(debug_str,	"_uart=%4X", tx_cfg.uart_only);
				string_zero_fill(debug_str);
				serial_send_string(debug_str);

				for(int c = 0; c < 7;c++)
				{
					xsprintf(debug_str,
										"_analog=[%2u,%4u,%4u]",
										tx_cfg.analog[c].n,
										tx_cfg.analog[c].min,
										tx_cfg.analog[c].max
									);
									string_zero_fill(debug_str);
									serial_send_string(debug_str);
				}
				serial_send_string("\n");


		break;
	case ACTION_GET_ASSERT:


		serial_send_string("************************************************");
		serial_send_string("\r\n");
		serial_send_string("Task  	    State   Prio    Stack    Num");
		serial_send_string("\r\n");
		serial_send_string("************************************************");
		serial_send_string("\r\n");

		serial_send_string(cBuffer);
		serial_send_string("************************************************");
		serial_send_string("\r\n");

/*
		for (loop_counter = 0; loop_counter < 100U; loop_counter++) {
					eeprom_read_variable(ASSERT_ERROR_MSG_ADDRESS + loop_counter, (uint16_t*)&debug_str[loop_counter]);
				}
				if (debug_str[0] == 0) {
					serial_send_string("No asserts.");
				}
				else {
					serial_send_string(debug_str);
				}
*/
		break;
	case ACTION_CLEAR_ASSERT:


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

			vTaskDelay(2/portTICK_RATE_MS);
		}


		/*
		uint8_t d1 = 0x12;
		uint8_t d2 = 0x34;
		uint16_t d3 = 0;
		uint8_t mul = 0;
		if(cfg_counter > 0)
		{
		for(uint8_t c = 0; c <= 16 ; c = c+2)
		{
			mul = c /2;
			d2 = buffer_8[c];
			d1 = buffer_8[c+1];
			d3 = (d1 << 8) | d2;
			buffer_16[mul] = d3;
		}

        usr_cfg_write_to_flash_buffer(buffer_16,8,cfg_counter);
		}
		*/
		serial_send_string("r");
		serial_send_string("\n");
		break;
	case ACTION_CFG_GET:
		for (loop_counter = 0; loop_counter < tx_cfg.fb_len; loop_counter++) {
					if (loop_counter == 2) {
						vTaskDelay(( TickType_t ) 1);
					}
					byte = *(__IO uint16_t*) (DATA_EEPROM_START_ADDR + loop_counter);
					xQueueSend(serial_tx_queue, (void*)&byte, ( TickType_t ) 1);
				}
				byte = tx_cfg.fb_crc >> 8;
				xQueueSend(serial_tx_queue, (void*)&byte, ( TickType_t ) 1);
				byte = tx_cfg.fb_crc & 0xFF;
				xQueueSend(serial_tx_queue, (void*)&byte, ( TickType_t ) 1);
				serial_send_string("\n");
				break;
	case ACTION_CFG_SAVE:
		vTaskDelay(1 / portTICK_RATE_MS);


		serial_send_string("e");
		serial_send_string("\n");

		//xsprintf(debug_str,"%u",cfg_length);
		//serial_send_string(debug_str);

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


	case ACTION_DEV_PRG_START:


		programmode = 1;
		HAL_FLASHEx_DATAEEPROM_Unlock();
		error_code &= CFG_CRC_ERR_BIT;
		osThreadSuspend(radio_threadHandle);
		osThreadSuspend(io_ctrl_threadHandle);

		 HAL_TIM_Base_Stop_IT(&htim11);

	//	osThreadSuspend(radio_threadHandle);
	//	osThreadSuspend(io_ctrl_threadHandle);

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

	case ACTION_DEV_RADIO_SET_PA:



		ascii_to_uint(cmd[2], cmd[3], &temp[0]);






			string_zero_fill(debug_str);
			serial_send_string(debug_str);

		serial_send_string("\r");
		serial_send_string("\n");


	//	while(1);
		break;


	case ACTION_DEV_RADIO_SET_PN9:
		programmode = 10;


		//ascii_to_uint(cmd[2], cmd[3], &pow);

		xsprintf(debug_str,	"PN9");
		string_zero_fill(debug_str);
		serial_send_string(debug_str);





		serial_send_string("\r");
		serial_send_string("\n");


	//	while(1);
		break;


	case ACTION_DEV_GO_BOOT:

		JumpToBootloader();
		/*
		  __HAL_RCC_PWR_CLK_ENABLE();
		  HAL_PWR_EnableBkUpAccess();  //use SRAM backup to store magic number;

		  if (*(__IO uint8_t*)0x20040000 == 212)
		  {  //is magic number correct?
		    *(__IO uint8_t*)0x20040000 = 0;
		    JumpToBootloader();
		  }
		  */
		break;

	case ACTION_DO_NOTHING:
	default:
		serial_send_string("Invalid command.");
		serial_send_string("\n");
		break;
	}
}



void usr_cfg_write_to_flash_buffer(uint16_t * buffer, uint16_t size,uint16_t adress)
{

	uint16_t frame_cnt =0;



				//EEPROM_Write(DATA_EEPROM_START_ADDR + frame_cnt,buffer[c]);

				SaveBuffer_EEPROM(DATA_EEPROM_START_ADDR + adress,buffer,size);

				vTaskDelay(2 / portTICK_RATE_MS);



}


uint16_t crc16_update(
	uint16_t crc,
	uint8_t data
) {
    data ^= (uint8_t) (crc & 0xFF);
    data ^= data << 4;
    return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}


/*
void JumpToBootloader(void)
{
  void (*SysMemBootJump)(void);
  volatile uint32_t addr = 0x1FFF0000;
  HAL_RCC_DeInit();

  SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL = 0;
  __disable_irq();
  __HAL_RCC_SYSCFG_CLK_ENABLE();           //make sure syscfg clocked
  __DSB();
  __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH();  //remap system memory to address 0x0000000
  __DSB();
  __ISB();
  SCB->VTOR = 0;                           //set vector table offset to 0
  SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));
  __set_MSP(*(uint32_t *)addr);
    SysMemBootJump();
}
*/

extern ADC_HandleTypeDef hadc;

extern SPI_HandleTypeDef hspi2;
#define STM32L152_HighDensitySysMemLocation (0x1FF00000)

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


BaseType_t xHigherPriorityTaskWoken;
portBASE_TYPE queue_status_isr = pdFALSE;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)
    {
    	//received[0]= USART1->DR;
    	queue_status_isr = xQueueSendFromISR( serial_rx_queue, &received, &xHigherPriorityTaskWoken );
    	HAL_UART_Receive_IT(&huart1, &received[0], 1);

    }





}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)  // change USART instance
    {

    }

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
