#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdint.h>
#include "../threads/config.h"

#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_def.h"
#include "stm32l1xx_hal_gpio.h"

	void init(void);
	//void S2_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
	uint16_t crc_update(uint16_t crc,uint8_t data);
	uint16_t crc16_update(uint16_t crc,uint8_t data);
	uint8_t  check_crc_eeprom(void);

	extern volatile uint8_t xTxDoneFlag;
	extern volatile uint8_t xRxDoneFlag;

extern xQueueHandle RF_RX_queue;
extern xQueueHandle serial_tx_queue;
extern xQueueHandle serial_rx_queue;

extern xSemaphoreHandle outputs_mutex;
extern xSemaphoreHandle programm_mutex;

#define ISR_ACTION_REQUIRED 1
#define ISR_IDLE            0


#define RADIO_RX_START 0
#define RADIO_RX_END 1
#define RADIO_TX_START 2
#define RADIO_TX_END 3
#define RADIO_TX_IDLE 4


void set_ios(uint8_t spi_count);
void read_eeprom(void);

typedef struct {
	uint8_t n;
	uint8_t size;
	uint8_t an_0;
	uint8_t an_1;
} _cfg_analog;

typedef struct {
	uint16_t fb_len; // 2B
	uint8_t cfg_ver; // 1B
	uint8_t tx_len; // 1B
	uint8_t fr_rx[8]; // 8B
	uint16_t dev_no[8]; // 16B
	uint8_t rx_len; // 1B
	uint8_t move_chk; // 1B
	uint8_t spi_cfg[12]; // 12B
	uint8_t pk_out[32]; // 32B
	uint8_t sg_ctl_i; // 1B
	uint8_t sg_ctl_o; // 1B
	uint8_t pk_err; // 1B
	uint8_t ired_in; // 1B
	_cfg_analog analog[8]; // 36B
	uint16_t an_bit; // 2B
	uint8_t a_tab_0[64]; // 64B				//80
	uint8_t a_tab_1[64]; // 64B
	uint8_t a_tab_2[64]; // 64B
	uint8_t a_tab_3[64]; // 64B
	uint8_t bit_stop; // 1B
	uint8_t offset; // 1B
	uint16_t toggle[4]; // 4B
	uint16_t tval_tab[10]; // 20B
	uint16_t pk_cfg[1536]; // 1536
	uint16_t fb_crc; // 2B
} _rx_cfg;


#define SRV_ACTIVE 		(1 << 0)
#define SRV_PLUS 		(1 << 1)
#define SRV_MINUS 		(1 << 2)
#define SRV_MIN 		(1 << 3)
#define SRV_ZOLW 		(1 << 4)
#define BAT_L 			(1 << 5)
#define BAT_M 			(1 << 6)
#define BAT_H 			(1 << 7)

typedef struct {						//Programowane zakresy SRV
	uint8_t MaxUp[8];
	uint8_t MaxDn[8];
	uint8_t MinUp[8];
	uint8_t MinDn[8];


}_ana_prg_user_array;


typedef struct {
	uint8_t first_start;
	_ana_prg_user_array ARRAY[3];
} _ana_prg_user;



extern volatile  _ana_prg_user ANA_USER_PRG __attribute__ ((section(".rf_ana_config")));
extern volatile const _rx_cfg rx_cfg __attribute__ ((section(".rf_config")));
extern uint16_t eeprom_virtual_adress_table[];
extern uint8_t rx_frame[30];
extern uint8_t tx_frame[30];
//extern uint8_t analog_rx_frame[10];

typedef struct {
	unsigned cfg_ver: 1;
	unsigned cfg_len: 1;
	unsigned cfg_crc: 1;
	unsigned main_ctrl: 1;
	unsigned pks_ctrl: 1;
	unsigned invalid_cfg: 1;
	unsigned supply_short: 1;
	unsigned supply_err: 1;
	unsigned spi_crc: 1;
	unsigned spi_disc: 1;
	unsigned spi_ext: 1;
} sys_error_t;
extern sys_error_t system_errors;
extern uint8_t radio_status;
extern uint8_t spi_error_cnt[6];
extern GPIO_TypeDef  *  gpio_port_array[];
extern  uint32_t gpio_pins_array[];
extern const uint32_t CONTROL_pins_array[];
extern char system_version_str[];
extern char system_frame_str[50];
extern char system_dev_no_str[7];
extern char debug_str[128];
extern uint8_t Radio_Mode;
extern uint8_t Radio_Mode_Last;
extern uint8_t radio_frame[30];
extern volatile uint8_t programmode;
extern int8_t RSSI;
extern uint8_t PQI;
extern uint8_t SPI_numbers;
extern uint16_t rx_address;
extern uint8_t sbo[22];
extern uint8_t sbi[22];
extern uint8_t FRAME_SPI_TX[8];
extern uint8_t RX_FRAME_LENGHT;
extern uint8_t TX_FRAME_LENGHT;
extern uint16_t RX_FRAME_READY;
extern uint8_t radio_frame[30];
extern uint8_t continous_rssi;
extern uint8_t RX_RF_Frame_out[30];


#ifdef __cplusplus
	}
#endif

#endif /* VARIABLES_H_ */
