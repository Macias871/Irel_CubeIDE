#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"
#include "variables.h"
#include "INOUT_thread.h"
#include "../Lib/crc.h"
#include "CMD_thread.h"




extern xQueueHandle Rs485_serial_rx_queue;
extern xQueueHandle Rs485_serial_tx_queue;
extern UART_HandleTypeDef huart1;

extern 	portBASE_TYPE queue_status;
extern 	portBASE_TYPE rx_queue_status;

volatile uint8_t received[1];




char cmd_table_U3[18];
char tmp_hex[2];
uint8_t cmd_String[48];
//uint8_t rs485_String[100];
char buffer_rs485_rx[30];
char chars[30];




void CMD_task(void const * argument) {
		uint8_t queue_first_byte_tx = 0;
		uint8_t queue_first_byte = 0;
		uint8_t cmd_item_counter = 0;

		HAL_UART_Receive_IT(&huart1, &received, 1);
		HAL_GPIO_WritePin(UDEN_GPIO_Port,UDEN_Pin, RESET);
		HAL_GPIO_WritePin(WORK_GPIO_Port,WORK_Pin,GPIO_PIN_SET);

	  for(;;)
	  {




		  rx_queue_status = xQueueReceive(Rs485_serial_rx_queue, &queue_first_byte, 1);


			if (rx_queue_status == pdPASS) {

				cmd_table_U3[cmd_item_counter] = (char)queue_first_byte;
				switch (queue_first_byte) {
				case 'z':
					cmd_item_counter = 0U;
					Rs485_received_execute(cmd_table_U3);
					break;
				case 0x02:
					cmd_item_counter = 0U;
					break;
				default:
					if (cmd_item_counter < 100U) {
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



			}

			  if((USART1->SR & USART_SR_RXNE) == 0)
			    {


				queue_status = xQueueReceive(Rs485_serial_tx_queue, &queue_first_byte_tx, 2);
				if (queue_status == pdPASS) {
					HAL_GPIO_WritePin(UDEN_GPIO_Port,UDEN_Pin, SET);
					for(uint8_t v =0; v< 100;v++){}
					HAL_UART_Transmit(&huart1,&queue_first_byte_tx,1,2);
					__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
					//HAL_UART_Transmit(&huart1,&queue_first_byte_tx,1,1);

				}
				else {
					for(uint8_t v =0; v< 100;v++){}
					 HAL_GPIO_WritePin(UDEN_GPIO_Port,UDEN_Pin, RESET);
				}
			  }

			taskYIELD();

	  }



}

BaseType_t xHigherPriorityTaskWoken;
portBASE_TYPE queue_status_isr = pdFALSE;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)
    {


    	queue_status_isr = xQueueSendFromISR( Rs485_serial_rx_queue, &received, &xHigherPriorityTaskWoken );
    	HAL_UART_Receive_IT(&huart1, &received, 1);

    }

}

uint16_t crc_rx;

void Rs485_received_execute(char *cmd)
{
	//hexStr2Arr(buffer_rs485,&cmd[1],8);

	memcpy(buffer_rs485_rx,&cmd[1],19);
	crc_rx = calc_crc(buffer_rs485_rx,14);

	//memset(chars,0,100);
	//chars[0] = datahex(buffer_rs485_rx[0]);
	hexStr2Arr(&chars[0],&buffer_rs485_rx[0],9);

	RX_Frame.crc = (chars[7] << 8) | (chars[8]);
	if(crc_rx == RX_Frame.crc )
	{
		RX_Frame.Adress = chars[0];
		RX_Frame.frame_count = (chars[1] << 8) | (chars[2]);
		RX_Frame.frame_Tstamp = (chars[3] << 8) | (chars[4]);
		RX_Frame.OUT= chars[5];
		RX_Frame.Mode= chars[6];
		RX_Frame.do_it = 1;



	}







}







void serial_send_string(char *str)
{

    uint8_t i = '\n';
    for (i = 0; ; i++) {

        if ((str[i] == '\0')) break;
        xQueueSend(Rs485_serial_tx_queue, (void*)&str[i], ( TickType_t ) 2);


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




void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{


    if (huart->Instance == USART3)  // change USART instance
    {


    }


    if (huart->Instance == USART1)  // change USART instance
    {}


}












void create_report(uint8_t pack_nr)				//WysyĹ‚anie raportu do esp8266
{}



