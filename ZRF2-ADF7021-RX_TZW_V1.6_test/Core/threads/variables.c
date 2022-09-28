/**

 */
#include "main.h"
#include "variables.h"
#include <stdint.h>
#include "../threads/config.h"
#include "../Lib/eeprom.h"

uint8_t tx_frame[30];
uint8_t rx_frame[30];
uint8_t RX_RF_Frame_out[30];
sys_error_t system_errors;
uint8_t spi_error_cnt[6];
uint8_t radio_status = 0;


uint8_t Radio_Mode=0;
uint8_t Radio_Mode_Last=0;

int8_t RSSI = 0;
uint8_t PQI = 0;
uint8_t SPI_numbers = 0;
uint16_t rx_address=0;
uint8_t sbo[22];
uint8_t sbi[22];
uint8_t FRAME_SPI_TX[8]={0x00,0x00,0x00,0x00,0x00,0x00,0,0xFF};
uint16_t RX_FRAME_READY = 0;
uint8_t radio_frame[30];
uint8_t continous_rssi = 0;
uint8_t tmp_frame[22];
uint8_t  packetSemaphore = 0;
volatile uint8_t programmode = 0;

volatile uint8_t xTxDoneFlag = RESET;
volatile uint8_t xRxDoneFlag = RESET;


uint8_t RX_FRAME_LENGHT = 11;
uint8_t TX_FRAME_LENGHT = 11;

volatile  _ana_prg_user ANA_USER_PRG __attribute__ ((section(".rf_ana_config")));
volatile const _rx_cfg rx_cfg __attribute__ ((section(".rf_config")));
/*
= {
	0xFFFF, // fb_len
	0xFF, // cfg_ver
	0x06, //tx_len
	{23, 24, 25, 26, 27, 28, 29, 30}, // fr_tx
	{3000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, // dev_no
	0x0e, // rx_len
	24, // move
	{
		0x90, 0x00, 0x91, 0x00, 0x92, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00
	}, // spi_cfg
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	}, // pk_out
	2, // sgi
	39, // sgo
	4, // pk_err
	0xff, //ired


	{
		{0xFF, 0xFF, 0xFF, 0xFF},
		{0xFF, 0xFF, 0xFF, 0xFF},
		{0xFF, 0xFF, 0xFF, 0xFF},
		{0xFF, 0xFF, 0xFF, 0xFF},
		{0xFF, 0xFF, 0xFF, 0xFF},
		{0xFF, 0xFF, 0xFF, 0xFF},
		{0xFF, 0xFF, 0xFF, 0xFF}
	}, // analog
	0xFF, //anbit
	0x00, //empty
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	}, // a_tab_0
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	}, // a_tab_1
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	}, // a_tab_2
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	}, // a_tab_3
	0x00, // bit_stop
	0x00, // offset
	{0xFF, 0xFF, 0xFF, 0xFF}, // toggle
	{0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x000A}, // tval_tab
	{0xffff
	},
	0xFFFF // fb_crc
};
*/


/*
uint16_t eeprom_virtual_adress_table[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
	70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
	90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
	100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
	110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
	130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
	140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
	150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
	160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
	170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
	180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
	190, 191, 192, 193, 194, 195, 196, 197, 198, 109,
	200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
	210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
	220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
	230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
	240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
	250, 251, 252, 253, 254, 255
};

*/


/**
 * @brief STM IO ports configuration table
 * @details When pin number isn't connected to GPIO then is marked as GPIOE.
 */
GPIO_TypeDef  * gpio_port_array[] = {
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
uint32_t gpio_pins_array[] = {
		0x00FF,	// [0] - NC
		0x00FF,	// [1] - VBAT
		0x00FF,	// [2] - PC13
		14,	// [3] - PC14
		0x00FF,	// [4] - PC15
		0x00FF,  // [5] - PD0*
		0x00FF,	// [6] - PD1*
		0x00FF,	// [7] - NRST
		0,	// [8] - PC0			P14
		1,	// [9] - PC1			P12
		2,	// [10] - PC2			A_CTRL
		0x00FF,	// [11] - PC3			A_CHK
		0x00FF,	// [12] - VSSA
		0x00FF,	// [13] - VDDA
		0,	// [14] - PA0		P10
		1,	// [15] - PA1		P8
		2,	// [16] - PA2		P2
		3,	// [17] - PA3		P6
		0x00FF,	// [18] - VSSA
		0x00FF,	// [19] - VDDA
		4,	// [20] - PA4		P4
		0x00FF,	// [21] - PA5
		0x00FF,	// [22] - PA6
		0x00FF,	// [23] - PA7
		0x00FF,	// [24] - PC4		Vbat
		5,	// [25] - PC5		P16
		0x00FF,	// [26] - PB0
		0x00FF,	// [27] - PB1
		0x00FF,	// [28] - PB2
		0x00FF,	// [29] - PB10
		0x00FF,	// [30] - PB11
		0x00FF,	// [31] - VSS_1
		0x00FF,	// [32] - VDD_1
		0x00FF,	// [33] - PB12			//RXTX
		13,	// [34] - PB13
		14,	// [35] - PB14
		15,	// [36] - PB15
		0x00FF,	// [37] - PC6
		0x00FF,	// [38] - PC7
		0x00FF,	// [39] - PC8
		0x00FF,	// [40] - PC9
		0x00FF,	// [41] - PA8
		0x00FF,	// [42] - PA9
		0x00FF,	// [43] - PA10
		0x00FF,	// [44] - PA11
		0x00FF,	// [45] - PA12
		0x00FF,	// [46] - PA13
		0x00FF,	// [47] - VSS_2
		0x00FF,	// [48] - VDD_2
		0x00FF,	// [49] - PA14
		0x00FF,	// [50] - PA15
		10,	// [51] - PC10			P7
		11,	// [52] - PC11			P18
		0x00FF,	// [53] - PC12
		0x00FF,	// [54] - PD2
		0x00FF,	// [55] - PB3*
		0x00FF,	// [56] - PB4*
		5,	// [57] - PB5
		6,	// [58] - PB6			k1
		7,	// [59] - PB7			k2
		0x00FF,	// [60] - BOOT0
		8,	// [61] - PB8				P22	SS
		9,	// [62] - PB9				P20
		0x00FF,	// [63] - VSS_3
		0x00FF	// [64] - VDD_3
};


const uint32_t CONTROL_pins_array[] = {
		0x00FF,	// [0] - NC
		0x00FF,	// [1] - VBAT
		0x00FF,	// [2] - PC13
		0x00FF,	// [3] - PC14
		0x00FF,	// [4] - PC15
		0x00FF,  // [5] - PD0*
		0x00FF,	// [6] - PD1*
		0x00FF,	// [7] - NRST
		0x00FF,	// [8] - PC0			P14
		0x00FF,	// [9] - PC1			P12
		0x00FF,	// [10] - PC2			A_CTRL
		3,	// [11] - PC3			A_CHK
		0x00FF,	// [12] - VSSA
		0x00FF,	// [13] - VDDA
		0x00FF,	// [14] - PA0		P10
		0x00FF,	// [15] - PA1		P8
		0x00FF,	// [16] - PA2		P2
		0x00FF,	// [17] - PA3		P6
		0x00FF,	// [18] - VSSA
		0x00FF,	// [19] - VDDA
		0x00FF,	// [20] - PA4		P4
		0x00FF,	// [21] - PA5
		0x00FF,	// [22] - PA6
		0x00FF,	// [23] - PA7
		0x00FF,	// [24] - PC4		Vbat
		0x00FF,	// [25] - PC5		P16
		0x00FF,	// [26] - PB0
		0x00FF,	// [27] - PB1
		0x00FF,	// [28] - PB2
		0x00FF,	// [29] - PB10
		0x00FF,	// [30] - PB11
		0x00FF,	// [31] - VSS_1
		0x00FF,	// [32] - VDD_1
		0x00FF,	// [33] - PB12			//RXTX
		0x00FF,	// [34] - PB13
		0x00FF,	// [35] - PB14
		0x00FF,	// [36] - PB15
		0x00FF,	// [37] - PC6
		0x00FF,	// [38] - PC7
		0x00FF,	// [39] - PC8
		0x00FF,	// [40] - PC9
		0x00FF,	// [41] - PA8
		0x00FF,	// [42] - PA9
		0x00FF,	// [43] - PA10
		0x00FF,	// [44] - PA11
		0x00FF,	// [45] - PA12
		0x00FF,	// [46] - PA13
		0x00FF,	// [47] - VSS_2
		0x00FF,	// [48] - VDD_2
		0x00FF,	// [49] - PA14
		15,	// [50] - PA15
		0x00FF,	// [51] - PC10			P7
		0x00FF,	// [52] - PC11			P18
		12,	// [53] - PC12
		0x00FF,	// [54] - PD2
		0x00FF,	// [55] - PB3*
		0x00FF,	// [56] - PB4*
		5,	// [57] - PB5
		0x00FF,	// [58] - PB6			k1
		0x00FF,	// [59] - PB7			k2
		0x00FF,	// [60] - BOOT0
		0x00FF,	// [61] - PB8				P22	SS
		0x00FF,	// [62] - PB9				P20
		0x00FF,	// [63] - VSS_3
		0x00FF	// [64] - VDD_3
};




char system_version_str[] = "v1.18";
char system_frame_str[50];
char system_dev_no_str[7];
char debug_str[128];

extern SPI_HandleTypeDef hspi2;


void set_ios(uint8_t spi_count)
{



	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();



	if(spi_count == 0)
	{
		//__HAL_RCC_SPI2_CLK_DISABLE();
		//HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
	}

	if(spi_count >= 1)
	{
		//gpio_pins_array[61] = 0xff;	//PB12	//SS
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
		  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
		  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
		  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
		  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		  hspi2.Init.CRCPolynomial = 10;
		  if (HAL_SPI_Init(&hspi2) != HAL_OK)
		  {
		    //Error_Handler();
		  }



	}
	if(rx_cfg.spi_cfg[0] > 0)
	{
		gpio_pins_array[4] = 0xff;	//OUTS_CHK	//SS2
	}





	  uint16_t pins_in_port_A = 0;
	  uint16_t pins_in_port_B = 0;
	  uint16_t pins_in_port_C = 0;


	  uint32_t pin = 0;

	  for(uint8_t o_pin = 0; o_pin < 64; o_pin++)
	  {
		  if(gpio_pins_array[o_pin] != 0x00ff)
		  {

			  pin = gpio_pins_array[o_pin];


			  if(gpio_port_array[o_pin] == GPIOA)
			  {
				  pins_in_port_A |= 1 << pin;
			  }

			  if(gpio_port_array[o_pin] == GPIOB)
			  {
				  pins_in_port_B |= 1 << pin;
			  }


			  if(gpio_port_array[o_pin] == GPIOC)
			  {
				  pins_in_port_C |= 1 << pin;
			  }


		  }


	  }


	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = pins_in_port_A;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = pins_in_port_B;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



	  GPIO_InitStruct.Pin = pins_in_port_C;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//*********************************************************************//


	  HAL_GPIO_WritePin(A_CTRL_GPIO_Port, A_CTRL_Pin, GPIO_PIN_SET);

		if(rx_cfg.spi_cfg[0] > 0)
		{
		}
		else
		{

		}


		  GPIO_InitStruct.Pin = SWD_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
		  GPIO_InitStruct.Pull = GPIO_PULLUP;
		  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


		  /*
		  GPIO_InitStruct.Pin = A_CTRL_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		  HAL_GPIO_Init(A_CTRL_GPIO_Port, &GPIO_InitStruct);

		  GPIO_InitStruct.Pin = A_CHK_Pin || M_CTRL_IN_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		  GPIO_InitStruct.Pull = GPIO_PULLUP;
		  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


		  GPIO_InitStruct.Pin = M_CTRL_OUT_Pin;
		  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
		  HAL_GPIO_Init(M_CTRL_OUT_GPIO_Port, &GPIO_InitStruct);
		   */



//**********************************************************************//



}


void read_eeprom(void)
{


	//memcpy(&ANA_USER_PRG,*(volatile uint32_t*)EEPROM_PAGE_ADDRESS,sizeof(ANA_USER_PRG) );
	//for (uint16_t i = 0; i < sizeof(ANA_USER_PRG); i++)
	//{
	//	&ANA_USER_PRG = (*(volatile uint32_t*)EEPROM_PAGE_ADDRESS+i);
	//}

	//ReadBuffer_EEPROM(EEPROM_PAGE_ADDRESS,ANA_USER_PRG,sizeof(ANA_USER_PRG));

	//cfg_actual_channel = EEPROM_Read(CFG_RADIO_CHANNEL_ADDRESS_Start + (tx_settings.NR*2));
}

void init(void)
{

	if(ANA_USER_PRG.first_start == 0)
	{
		for(uint8_t c = 0; c < 8; c++)
		{
			ANA_USER_PRG.ARRAY[0].MaxDn[c] = 60;
			ANA_USER_PRG.ARRAY[0].MaxUp[c] = 60;
			ANA_USER_PRG.ARRAY[0].MinDn[c] = 1;
			ANA_USER_PRG.ARRAY[0].MinUp[c] = 1;

			ANA_USER_PRG.ARRAY[1].MaxDn[c] = 50;
			ANA_USER_PRG.ARRAY[1].MaxUp[c] = 50;
			ANA_USER_PRG.ARRAY[1].MinDn[c] = 1;
			ANA_USER_PRG.ARRAY[1].MinUp[c] = 1;

			ANA_USER_PRG.ARRAY[2].MaxDn[c] = 40;
			ANA_USER_PRG.ARRAY[2].MaxUp[c] = 40;
			ANA_USER_PRG.ARRAY[2].MinDn[c] = 1;
			ANA_USER_PRG.ARRAY[2].MinUp[c] = 1;
		}
		ANA_USER_PRG.first_start = 1;
	}
}

uint16_t crc_update(uint16_t crc,uint8_t data)
{
    data ^= (uint8_t) (crc & 0xFF);
    data ^= data << 4;
    return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}

uint16_t crc16_update(
	uint16_t crc,
	uint8_t data
) {
    data ^= (uint8_t) (crc & 0xFF);
    data ^= data << 4;
    return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}


uint8_t check_crc_eeprom(void)
{
	  uint16_t crc_eeprom= 0;
	  uint16_t cfg_crc_calc = 0xFFFF;
  	uint16_t cfg_len = (*(__IO uint16_t*) (DATA_EEPROM_START_ADDR+1 ) << 8) | *(__IO uint16_t*) (DATA_EEPROM_START_ADDR  );
  	if(cfg_len < 0xffff)
  	{
  	crc_eeprom = (*(__IO uint16_t*) (DATA_EEPROM_START_ADDR + cfg_len +1  ) << 8) | *(__IO uint16_t*) (DATA_EEPROM_START_ADDR  + cfg_len+0);

  	for (uint16_t loop_counter = 0U; loop_counter < cfg_len ; loop_counter++) {
  		uint8_t byte = *(__IO uint16_t*) (DATA_EEPROM_START_ADDR + loop_counter);
  		cfg_crc_calc = crc16_update(cfg_crc_calc, byte);}
  	}
  	if(crc_eeprom == cfg_crc_calc){return 0;}else{return 1;}
}
