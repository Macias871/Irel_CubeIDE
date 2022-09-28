
#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <stdint.h>
#include "stm32l1xx_hal.h"
#include "cmsis_os.h"
//#include "../config.h"
#define outputs_count 20

extern xQueueHandle serial_tx_queue;
extern xQueueHandle serial_rx_queue;
extern xSemaphoreHandle setup_mutex;
extern xSemaphoreHandle tx_frame_mutex;
extern xSemaphoreHandle off_counter_reset_mutex;

extern volatile uint8_t xTxDoneFlag;
extern volatile uint8_t xRxDoneFlag;

extern GPIO_TypeDef * gpio_port_array[];
extern volatile  uint32_t gpio_pins_array[];

void set_ios(uint8_t spi_count);
uint8_t  check_crc_eeprom(void);

extern volatile uint8_t programmode;


typedef struct {
	uint32_t PIN;
	GPIO_TypeDef * PORT;
} _output_pins;

//_output_pins Outputs[outputs_count];

/*
typedef struct {
	_output_pins OUTPUTS[outputs_count];
} _Outputs;
*/

typedef struct {
	uint16_t n;
	uint16_t min;
	uint16_t max;
} _cfg_analog;

typedef struct {
	uint8_t pin_no;
	uint8_t bit_no;
	uint8_t flags;
} _cfg_ktab_cnv;

typedef struct {
	uint16_t fb_len; // 2B
	uint16_t cfg_ver; // 2B
	uint16_t off_time1; // 2B
	uint16_t off_time2; // 2B
	uint16_t off_time3; // 2B
	uint16_t ired1; // 2B
	uint16_t ired2; // 2B
	uint8_t rx_len; // 1B
	uint8_t byte_offset; // 1B
	uint8_t fr_tx[8]; // 8B
	uint16_t dev_no[8]; // 16B
	uint16_t dev_no_Z;
	uint8_t num_sel[3]; // 3B
	uint8_t cfg_sel[3]; // 3B
	uint8_t tx_len; // 1B
	uint8_t crc_type; // 1B
	uint8_t spi_cfg[8]; // 8B
//	uint8_t rx_cnf[18]; // 18B
	uint8_t uart_only; // 1B
	uint8_t TOFFE;
	uint8_t srv_key[4];
	_cfg_analog analog[8]; // 42B
	_cfg_ktab_cnv ktab_cnv[512]; // 512B
	uint16_t fb_crc; // 2B
} _tx_cfg;


extern  _tx_cfg tx_cfg __attribute__ ((section(".rf_config")));

typedef struct {
	uint8_t CH;
	uint8_t PW;
	uint16_t NR;
	uint8_t spi_cnt;
	uint8_t spi_cfg[8];
} _tx_settings;

extern _tx_settings tx_settings;

typedef struct {
	uint8_t SRV_ACT;
	uint8_t SRV_MIN;
	uint8_t SRV_PLUS;
	uint8_t SRV_MINUS;
} _SRV;

extern _SRV SRV;





/*
typedef struct {
	uint8_t SYNC[3];
	uint8_t START_B;
	uint8_t STOP_B;
	uint8_t SRV_B;
	int8_t RSSI;
	uint16_t Num;
	uint16_t Crc;
	uint8_t PAYLOAD[];
} _ADF_PACKET;
extern _ADF_PACKET TX_ADF_PACKET;
extern _ADF_PACKET RX_ADF_PACKET;
*/





extern uint8_t off_counter_reset_glob;
extern uint8_t anal_count;
extern char cBuffer[255];
extern uint16_t bat_voltage;


extern uint8_t assert_counter;

extern uint8_t tx_frame[30];
extern uint8_t rx_frame[30];
extern uint8_t error_code;

extern uint8_t error_code;
#define CFG_VER_ERR_BIT (1 << 0)
#define CFG_LEN_ERR_BIT (1 << 1)
#define CFG_CRC_ERR_BIT (1 << 2)
#define CFG_SPI_ERR_BIT (1 << 3)

#define SRV_ACTIVE 		(1 << 0)
#define SRV_PLUS 		(1 << 1)
#define SRV_MINUS 		(1 << 2)
#define SRV_MIN 		(1 << 3)
#define SRV_ZOLW 		(1 << 4)
#define BAT_L 			(1 << 5)
#define BAT_M 			(1 << 6)
#define BAT_H 			(1 << 7)

#define KEY_CFG_OFF_RESET 0x01
#define KEY_CFG_ANALOG 0x02
#define KEY_CFG_INVERT 0x04
#define KEY_CFG_OUTPUT 0x08
#define KEY_CFG_STOP_ON	0x80



extern volatile uint16_t system_adc_values[10];
extern uint16_t cfg_actual_channel_q;
extern uint16_t cfg_actual_power_q;

extern char debug_str[150];
extern uint32_t stop_counter;

extern char system_frame_str[50];
extern char system_dev_no_str[7];
extern uint8_t BB_START;
extern uint8_t BB_STOP;


extern uint8_t Frm_cnt;
extern uint8_t state;
extern int8_t RSSI;
extern uint8_t rssiOffset;
extern uint8_t SRV_BYTE;
extern uint8_t setup_flag;

extern uint16_t CFG_VERSION;
extern uint16_t SYS_LOW_BATTERY_LEVEL;
extern uint16_t SYS_HIGH_BATTERY_LEVEL;



extern uint8_t spi_cnt;
extern uint8_t TX_FRAME_LENGHT;
extern uint8_t RX_FRAME_LENGHT;


#endif /* VARIABLES_H_ */
