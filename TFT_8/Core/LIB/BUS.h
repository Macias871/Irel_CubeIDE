#ifndef BUS_INC_H
#define BUS_INC_H



#include <string.h>
#include "main.h"
#include "cmsis_os.h"

void BusDriverEnable(void);
void BusDriverDisable(void);
void UARTSendDataByte(UART_HandleTypeDef * UART, char * datas, uint8_t len);
void UARTReadDataByte(UART_HandleTypeDef * UART, char * datas, uint8_t len);

/* ustawienia */
#define PWMSlave

//#define TEMP_NTC
//#define TEMP_PT
//#define TEMP_PT_NTC

#define USE_NTC_FILTER
#define USE_NTC_ERR
#define NTC_MAX_VAL		1000
//#define BusDriverEnable()	PORTG |= (1 << 13)
//#define BusDriverDisable()	PORTG &=~ (1 << 13)

#define BusTxFrameSize		6
#define BusTxHeader		0x0F

#define S1addr			0x31
#define S2addr			0x32
#define CmdGetInSetOut		0x01
#define SlavesNumber		0x07
#define MAX_ABSENCE             50
#define NTC80_MAX               3500
#define NTC80_MIN               1650
#define NTC60_MAX               4000
#define NTC60_MIN               140
#define NTC30_MAX               3330
#define NTC30_MIN               665 // (equivalent to +48*C)
#define PT1000_MAX              2500
#define PT1000_MIN              10

#define DEBUG_PREFIX_REFRESH    1U
#define DEBUG_PREFIX_UPDATE     2U
#define DEBUG_PREFIX_ETH        3U
#define DEBUG_PREFIX_SYS        4U

typedef struct {
    char AN0[4];
    char AN1[4];
    char AN2[4];
    char AN3[4];
    char AN4[4];
    char AN5[4];
    char AN6[4];
    char AN7[4];
    char DI[2];
} __inputs;

typedef struct {
    uint8_t Address;
    uint16_t Analog0;
    uint16_t Analog1;
    uint16_t Analog2;
    uint16_t Analog3;
    uint16_t Analog4;
    uint16_t Analog5;
    uint16_t Analog6;
    uint16_t Analog7;
    uint8_t Inputs;
    uint16_t Crc;
} _slaveFrame;
extern _slaveFrame slaveFrameRaw;
#ifdef PWMSlave
typedef struct {
    uint8_t Address;
    uint8_t St;
    uint8_t PWM1;
    uint8_t PWM2;
    uint16_t temp;
    uint8_t inp;
    uint16_t Crc;
} _slavePWMFrame;
extern _slavePWMFrame slavePWMFrameRaw;
#endif
/**
 * @brief RS485 maintain task
 * @param pvParameters Parameters not used in task
 */
void task_bus(void);

/**
 * @brief Debug task
 * @param pvParameters Parameters not used in task
 */
void task_debug(void);

/**
 * @brief Send single byte to debug
 * @param val value to be send
 */
void debug_byte_send(uint8_t val);

/**
 * @brief Send message to debug port
 * @param prefix debug prefix
 * @param msg message to be send
 */
void debug_msg_send(uint8_t prefix, char *msg);

/**
 * @brief Temperature conversion
 * @param prec Temperature in XX.X format
 * @param cmpns not used
 * @param minValue minimum value
 * @param maxValue maximum value
 * @param conditionToZero if this condition is true then output value is zero
 * @return converted temperature
 */
float temperature_convert_to_normal(float prec, float cmpns, int16_t minValue, int16_t maxValue, int16_t conditionToZero);

/**
 * @brief Frame conversion
 * @param frame input frame
 * @param size size of input frame
 * @param slave pointer to slave struct
 * @return always 0
 */
int8_t frame_convert(char* frame, uint8_t size, _slaveFrame *slave);

int8_t PWMframe_convert(char* frame, uint8_t size, _slavePWMFrame *slave);

/**
 * @brief Get item from frame string
 * @param frame pointer to frame string
 * @param start start address
 * @param clipped pointer to clipped string
 * @param size size of clipped string
 * @return
 * - 0 if unknown format
 * - other if ok
 */
uint16_t frame_get_item(char* frame, uint8_t start, char* clipped, uint8_t size);

/**
 * @brief Get data from raw slave structure
 * @param raw slave structure
 * @param slaveIndex index of slave
 * @param cmpnsStart unused
 * @param clrFlag if 1 count for slave absence
 * @return event id for log function
 */
uint8_t frame_get_data(_slaveFrame * raw, uint8_t slaveIndex, uint8_t cmpnsStart, uint8_t clrFlag);

uint8_t PWMframe_get_data(_slavePWMFrame * raw, uint8_t slaveIndex, uint8_t cmpnsStart, uint8_t clrFlag);

/**
 * @brief Check for value update. If prvVal not equal with actVal then set _bit in gui_refresh_bits_0 and return actVal.
 * @param prvVal prev value
 * @param actVal actual value
 * @param _bit bit possition in gui_refresh_bits_0 variable
 * @return actVal
 */
int16_t check_to_update(int16_t prvVal, int16_t actVal, uint8_t _bit);

/**
 * @brief Clip variable to maximum value.
 * @param value value of variable
 * @param max maximum accepted value
 * @return value of clipped variable
 */
uint16_t clip_max_value(uint16_t value, uint16_t max);

#endif /* BUS_INC_H */


