
#include "../../config.h"
#include "../lib/eeprom.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
//#include "cmsis_os.h"
//#include "stm32l1xx_hal.h"
#include "main.h"
#include "variables.h"



xQueueHandle ADF_RX_queue;
xQueueHandle serial_tx_queue;
xQueueHandle serial_rx_queue;
xSemaphoreHandle setup_mutex;
xSemaphoreHandle tx_frame_mutex;
xSemaphoreHandle off_counter_reset_mutex;

uint8_t tx_frame[30];
uint8_t rx_frame[30];

volatile uint8_t programmode = 0;

uint8_t lsb_tmp = 0;
uint8_t msb_tmp = 0;

uint32_t stop_counter = 0U;
//uint8_t tx_frame[PACKET_LENGTH+1];

uint8_t spi_cnt = 0;
uint8_t radio_mode = 0;
uint8_t sate_arr[6];
uint8_t Frm_cnt = 0;
uint8_t error_code = 0xFF;
uint8_t off_counter_reset_glob = 0;
uint8_t assert_counter = 0;
int8_t RSSI = 0;
uint8_t rssiOffset = 102;

uint16_t bat_voltage = 0;
char cBuffer[255];
uint8_t SRV_BYTE = 0;
uint8_t setup_flag = 0;
uint16_t Actual_tx_number = 0;
uint16_t CFG_VERSION = 0;
uint16_t SYS_LOW_BATTERY_LEVEL = 0;
uint16_t SYS_HIGH_BATTERY_LEVEL =0;
uint8_t TX_FRAME_LENGHT = 0;
uint8_t RX_FRAME_LENGHT = 0;

volatile uint8_t xTxDoneFlag = RESET;
volatile uint8_t xRxDoneFlag = RESET;

volatile uint16_t system_adc_values[10];
uint8_t anal_count = 1;

_tx_cfg tx_cfg __attribute__ ((section(".rf_config"))) ;
_tx_settings tx_settings;
_SRV SRV;
_output_pins Outputs[outputs_count];


/**
 * @brief STM IO ports configuration table
 * @details When pin number isn't connected to GPIO then is marked as GPIOE.
 */
GPIO_TypeDef * gpio_port_array[] = {
	GPIOE,	// [0] - NC
	GPIOE,	// [1] - VBAT
	GPIOC,	// [2] - PC13
	GPIOC,	// [3] - PC14
	GPIOC,	// [4] - PC15
	GPIOD,  // [5] - PD0*
	GPIOD,	// [6] - PD1*
	GPIOE,	// [7] - NRST
	GPIOC,	// [8] - PC0
	GPIOC,	// [9] - PC1
	GPIOC,	// [10] - PC2
	GPIOC,	// [11] - PC3
	GPIOE,	// [12] - VSSA
	GPIOE,	// [13] - VDDA
	GPIOA,	// [14] - PA0
	GPIOA,	// [15] - PA1
	GPIOA,	// [16] - PA2
	GPIOA,	// [17] - PA3
	GPIOE,	// [18] - VSSA
	GPIOE,	// [19] - VDDA
	GPIOA,	// [20] - PA4
	GPIOA,	// [21] - PA5
	GPIOA,	// [22] - PA6
	GPIOA,	// [23] - PA7
	GPIOC,	// [24] - PC4
	GPIOC,	// [25] - PC5
	GPIOB,	// [26] - PB0
	GPIOB,	// [27] - PB1
	GPIOB,	// [28] - PB2
	GPIOB,	// [29] - PB10
	GPIOB,	// [30] - PB11
	GPIOE,	// [31] - VSS_1
	GPIOE,	// [32] - VDD_1
	GPIOB,	// [33] - PB12
	GPIOB,	// [34] - PB13
	GPIOB,	// [35] - PB14
	GPIOB,	// [36] - PB15
	GPIOC,	// [37] - PC6
	GPIOC,	// [38] - PC7
	GPIOC,	// [39] - PC8
	GPIOC,	// [40] - PC9
	GPIOA,	// [41] - PA8
	GPIOA,	// [42] - PA9
	GPIOA,	// [43] - PA10
	GPIOA,	// [44] - PA11
	GPIOA,	// [45] - PA12
	GPIOA,	// [46] - PA13
	GPIOE,	// [47] - VSS_2
	GPIOE,	// [48] - VDD_2
	GPIOA,	// [49] - PA14
	GPIOA,	// [50] - PA15
	GPIOC,	// [51] - PC10
	GPIOC,	// [52] - PC11
	GPIOC,	// [53] - PC12
	GPIOD,	// [54] - PD2
	GPIOB,	// [55] - PB3*
	GPIOB,	// [56] - PB4*
	GPIOB,	// [57] - PB5
	GPIOB,	// [58] - PB6
	GPIOB,	// [59] - PB7
	GPIOE,	// [60] - BOOT0
	GPIOB,	// [61] - PB8
	GPIOB,	// [62] - PB9
	GPIOE,	// [63] - VSS_3
	GPIOE	// [64] - VDD_3

};

/**
 * @brief STM IO pins configuration table
 * @details When pin has no permission to configure by user in cfg then is marked as 0xFF.
 */
volatile uint32_t gpio_pins_array[] = {
		0xFF,	// [0] - NC
		0xFF,	// [1] - VBAT
		0xFF,	// [2] - PC13
		0xFF,	// [3] - PC14
		15,		// [4] - PC15			P24
		0xFF,   // [5] - PD0*
		0xFF,	// [6] - PD1*
		0xFF,	// [7] - NRST
		0,		// [8] - PC0			P16
		1,	// [9] - PC1
		2,	// [10] - PC2			P12
		3,		// [11] - PC3			P10
		0xFF,	// [12] - VSSA
		0xFF,	// [13] - VDDA
		0,		// [14] - PA0			P6
		1,		// [15] - PA1			P4
		2,		// [16] - PA2			P2
		3,		// [17] - PA3			P8
		0xFF,	// [18] - VSSA
		0xFF,	// [19] - VDDA
		4,		// [20] - PA4			P12
		0xFF,	// [21] - PA5
		0xFF,	// [22] - PA6
		0xFF,	// [23] - PA7
		0xFF,		// [24] - PC4			Vbat
		5,		// [25] - PC5			P16
		0xFF,	// [26] - PB0
		0xFF,	// [27] - PB1
		0xFF,	// [28] - PB2
		0xFF,	// [29] - PB10
		0xFF,	// [30] - PB11
		0xFF,	// [31] - VSS_1
		0xFF,	// [32] - VDD_1
		0xFF,	// [33] - PB12
		13,		// [34] - PB13
		14,		// [35] - PB14
		15,		// [36] - PB15
		0xFF,	// [37] - PC6
		0xFF,		// [38] - PC7			P15
		0XFF,		// [39] - PC8			P17
		0XFF,	// [40] - PC9
		0xFF,	// [41] - PA8
		0xFF,	// [42] - PA9
		0xFF,	// [43] - PA10
		11,	// [44] - PA11
		12,	// [45] - PA12
		0xFF,	// [46] - PA13
		0xFF,	// [47] - VSS_2
		0xFF,	// [48] - VDD_2
		0xFF,	// [49] - PA14
		15,	// [50] - PA15
		10,		// [51] - PC10			P7
		0xFF,	// [52] - PC11
		12,	// [53] - PC12
		0xFF,	// [54] - PD2
		0xFF,	// [55] - PB3
		0xFF,	// [56] - PB4
		5,		// [57] - PB5			P22		IR
		0xFF,		// [58] - PB6			P21
		7,		// [59] - PB7			P23
		0xFF,	// [60] - BOOT0
		8,	// [61] - PB8
		9,	// [62] - PB9
		0xFF,	// [63] - VSS_3
		0xFF	// [64] - VDD_3
};

volatile uint32_t gpio_output_pins_array[64];
char system_frame_str[50];
char system_dev_no_str[7];

char buff_str[1];
/**
 * @brief Start button
 */
uint8_t BB_START = 0;

/**
 * @brief Stop button
 */
uint8_t BB_STOP = 0;



extern SPI_HandleTypeDef hspi2;

void set_ios(uint8_t spi_count)
{

	  tx_settings.spi_cnt = spi_count;

	  memcpy(&tx_settings.spi_cfg[0], &tx_cfg.spi_cfg[0],8);		//Kopiowanie ustawień spi do osobnej struktury.


	GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();



	if(tx_settings.spi_cnt == 0)
	{
		//__HAL_RCC_SPI2_CLK_DISABLE();
		//HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	}

	if(tx_settings.spi_cnt >= 1)
	{
		//gpio_pins_array[44] = 0xff;	//PB8	//SS PA11
		gpio_pins_array[34] = 0xff;	//PB13	//SCK
		gpio_pins_array[35] = 0xff;	//PB14	//MISO
		gpio_pins_array[36] = 0xff;	//PB15	//MOSI


		  hspi2.Instance = SPI2;
		  hspi2.Init.Mode = SPI_MODE_MASTER;
		  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
		  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
		  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
		  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
		  hspi2.Init.NSS = SPI_NSS_SOFT;
		  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
		  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
		  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
		  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		  hspi2.Init.CRCPolynomial = 10;
		  if (HAL_SPI_Init(&hspi2) != HAL_OK)
		  {
		    //Error_Handler();
		  }



	}

	if(tx_settings.spi_cfg[1] != 0)
	{

		  gpio_pins_array[44] = 0xff;	//PA11	//SS1
		  GPIO_InitStruct.Pin = SS1_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		  HAL_GPIO_Init(SS1_GPIO_Port, &GPIO_InitStruct);
	}


	if(tx_settings.spi_cfg[3] != 0)
	{

		  gpio_pins_array[61] = 0xff;	//PB8	//SS2
		  GPIO_InitStruct.Pin = SS2_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		  HAL_GPIO_Init(SS2_GPIO_Port, &GPIO_InitStruct);
	}

	if(tx_settings.spi_cfg[5] != 0)
	{

		  gpio_pins_array[50] = 0xff;	//PA15	//SS3
		  GPIO_InitStruct.Pin = SS3_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		  HAL_GPIO_Init(SS3_GPIO_Port, &GPIO_InitStruct);
	}

	if(tx_settings.spi_cfg[7] != 0)
	{

		  gpio_pins_array[45] = 0xff;	//PA12	//SS4
		  GPIO_InitStruct.Pin = SS4_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		  HAL_GPIO_Init(SS4_GPIO_Port, &GPIO_InitStruct);
	}



	if(tx_cfg.analog[0].n >= 1)			//PC2 5A10	10
	{
		gpio_pins_array[10] = 0xff;

	    GPIO_InitStruct.Pin = GPIO_PIN_2;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	    anal_count++;

	}

	if((tx_cfg.analog[1].n) >=  1)			//PC3 5A32	11
	{
		gpio_pins_array[11] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	    anal_count++;
	}

	if((tx_cfg.analog[2].n) >=  1)			//PA0 2A10	14
	{
		gpio_pins_array[14] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_0;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	    anal_count++;
	}

	if((tx_cfg.analog[3].n) >=  1)			//PA1 2A32	15
	{
		gpio_pins_array[15] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_1;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	    anal_count++;
	}

	if((tx_cfg.analog[4].n) >=  1)			//PA2 5A45	16
	{
		gpio_pins_array[16] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_2;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	    anal_count++;
	}

	if((tx_cfg.analog[5].n) >=  1)			//PA3 2A6	17
	{
		gpio_pins_array[17] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	    anal_count++;
	}

	if((tx_cfg.analog[6].n) >=  1)			//PA4 2A45	20
	{
		gpio_pins_array[20] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_4;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	    anal_count++;
	}

	if((tx_cfg.analog[7].n) >=  1)			//PC1 2W4	9
	{
		gpio_pins_array[9] = 0xff;
	    GPIO_InitStruct.Pin = GPIO_PIN_1;
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	    anal_count++;
	}







	  uint16_t OUTPUT_pins_in_port_A = 0;
	  uint16_t OUTPUT_pins_in_port_B = 0;
	  uint16_t OUTPUT_pins_in_port_C = 0;
	  uint16_t OUTPUT_pins_in_port_H = 0;


	  uint16_t INPUT_pins_in_port_A = 0;
	  uint16_t INPUT_pins_in_port_B = 0;
	  uint16_t INPUT_pins_in_port_C = 0;
	  uint16_t INPUT_pins_in_port_H = 0;


	  uint32_t pin = 0;



	  for(uint8_t stm_p_pin = 0;stm_p_pin< outputs_count;stm_p_pin++ ){
			if ((tx_cfg.ktab_cnv[stm_p_pin].flags & KEY_CFG_OUTPUT)) 			//Tryb wyjscia pinu
			{


			 if(tx_cfg.ktab_cnv[stm_p_pin].bit_no < outputs_count)
			 {
				 uint8_t table_pos_nr = tx_cfg.ktab_cnv[stm_p_pin].pin_no;
				 uint8_t pin_nr = gpio_pins_array[table_pos_nr];
				 gpio_output_pins_array[table_pos_nr] = gpio_pins_array[table_pos_nr];

				 uint8_t bit_nr = tx_cfg.ktab_cnv[stm_p_pin].bit_no;

				 Outputs[bit_nr].PIN = 1 << pin_nr;
				 Outputs[bit_nr].PORT = gpio_port_array[table_pos_nr];

				 gpio_pins_array[table_pos_nr] = 0xFE;

				 /*
				 gpio_output_pins_array[tx_cfg.ktab_cnv[stm_p_pin].pin_no] = pin_nr;
				Outputs[tx_cfg.ktab_cnv[stm_p_pin].bit_no].PIN = gpio_pins_array[tx_cfg.ktab_cnv[stm_p_pin].pin_no];
				Outputs[tx_cfg.ktab_cnv[stm_p_pin].bit_no].PORT = gpio_port_array[tx_cfg.ktab_cnv[stm_p_pin].pin_no];
				HAL_GPIO_WritePin(gpio_port_array[tx_cfg.ktab_cnv[stm_p_pin].pin_no], gpio_pins_array[tx_cfg.ktab_cnv[stm_p_pin].pin_no], RESET);
				 gpio_pins_array[tx_cfg.ktab_cnv[stm_p_pin].pin_no] = 0xFE;
				 */
			 }


			}
	  }

	  for(uint8_t o_pin = 0; o_pin < 64; o_pin++)
	  {



		  if(gpio_pins_array[o_pin] != 0x00FF && gpio_pins_array[o_pin] != 0x00FE)
		  {
			  pin = gpio_pins_array[o_pin];
			  if(gpio_port_array[o_pin] == GPIOA)
			  {
				  INPUT_pins_in_port_A |= 1 << pin;
			  }

			  if(gpio_port_array[o_pin] == GPIOB)
			  {
				  INPUT_pins_in_port_B |= 1 << pin;
			  }


			  if(gpio_port_array[o_pin] == GPIOC)
			  {
				  INPUT_pins_in_port_C |= 1 << pin;
			  }


			  if(gpio_port_array[o_pin] == GPIOH)
			  {
				  INPUT_pins_in_port_H |= 1 << pin;
			  }
		  }

		  if(gpio_pins_array[o_pin] == 0x00FE)
		  {
			  pin = gpio_output_pins_array[o_pin];
			  if(gpio_port_array[o_pin] == GPIOA)
			  {
				  OUTPUT_pins_in_port_A |= 1 << pin;
			  }

			  if(gpio_port_array[o_pin] == GPIOB)
			  {
				  OUTPUT_pins_in_port_B |= 1 << pin;
			  }


			  if(gpio_port_array[o_pin] == GPIOC)
			  {
				  OUTPUT_pins_in_port_C |= 1 << pin;
			  }


			  if(gpio_port_array[o_pin] == GPIOH)
			  {
				  OUTPUT_pins_in_port_H |= 1 << pin;
			  }
		  }
	  }



	  GPIO_InitStruct.Pin = INPUT_pins_in_port_A;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = INPUT_pins_in_port_B;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = INPUT_pins_in_port_C;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


	  GPIO_InitStruct.Pin = INPUT_pins_in_port_H;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);


	  GPIO_InitStruct.Pin = OUTPUT_pins_in_port_A;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = OUTPUT_pins_in_port_B;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = OUTPUT_pins_in_port_C;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


	  GPIO_InitStruct.Pin = OUTPUT_pins_in_port_H;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);






//********************************************************************************//




	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, POFF_Pin|CE_Pin|SLE_Pin|BEEP_Pin
	                          |LEDR_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOA, SCLK_Pin|SDATA_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(RXTX_GPIO_Port, RXTX_Pin, GPIO_PIN_SET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOB, LEDG_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : POFF_Pin BEEP_Pin LEDR_Pin */
	  GPIO_InitStruct.Pin = POFF_Pin|BEEP_Pin|LEDR_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



	  /*Configure GPIO pins : P10_Pin P8_Pin P2_Pin P6_Pin
	                           SREAD_Pin P23_Pin P21_Pin P24_Pin */
	  GPIO_InitStruct.Pin =SREAD_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



	  /*Configure GPIO pins : SCLK_Pin SDATA_Pin */
	  GPIO_InitStruct.Pin = SCLK_Pin|SDATA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /*Configure GPIO pin : SWD_Pin */
	  GPIO_InitStruct.Pin = SWD_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(SWD_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : MUXOUT_Pin */
	  GPIO_InitStruct.Pin = MUXOUT_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(MUXOUT_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : RXTX_Pin SS_Pin */
	  GPIO_InitStruct.Pin = RXTX_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : CE_Pin SLE_Pin */
	  GPIO_InitStruct.Pin = CE_Pin|SLE_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



	  /*Configure GPIO pin : PON_Pin */
	  GPIO_InitStruct.Pin = PON_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(PON_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : LEDG_Pin */
	  GPIO_InitStruct.Pin = LEDG_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(LEDG_GPIO_Port, &GPIO_InitStruct);

	  /* EXTI interrupt init*/
	  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	  HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
	  HAL_NVIC_EnableIRQ(EXTI1_IRQn);










}








uint8_t check_crc_eeprom(void)
{
	  uint16_t crc_eeprom= 0;
  	uint16_t cfg_len = (*(__IO uint16_t*) (DATA_EEPROM_START_ADDR+1 ) << 8) | *(__IO uint16_t*) (DATA_EEPROM_START_ADDR  );
  	crc_eeprom = (*(__IO uint16_t*) (DATA_EEPROM_START_ADDR + cfg_len +1  ) << 8) | *(__IO uint16_t*) (DATA_EEPROM_START_ADDR  + cfg_len+0);
  	uint16_t cfg_crc_calc = 0xFFFF;
  	for (uint16_t loop_counter = 0U; loop_counter < cfg_len ; loop_counter++) {
  		uint8_t byte = *(__IO uint16_t*) (DATA_EEPROM_START_ADDR + loop_counter);
  		cfg_crc_calc = crc16_update(cfg_crc_calc, byte);}

  	if(crc_eeprom == cfg_crc_calc){return 0;}else{return 1;}
}
