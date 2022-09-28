

#ifndef CONFIG_H_
#define CONFIG_H_

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"






/**
* @brief Status LED blink interval [x 10ms]
*/
#define STATUS_LED_BLINK_INTERVAL 25U

/**
 * @brief Transmitter power level (from 0 to 8)
 */
#define RADIO_POWER_LEVEL 3U

/**
* @brief Disconnect time of receiver module
* @details When this time is elapsed receiver module will reset outputs
*/
#define RX_DISCONNECT_TIME 50000U

/**
 * @brief Address of channel number in memory
 */
#define CFG_RADIO_CHANNEL_ADDRESS_Start 0x08080F00
#define CFG_RADIO_CHANNEL_ADDRESS_Stop  0x08080F0F

/**
 * @brief Address of power level in memory
 */
#define CFG_RADIO_POWER_ADDRESS_START 0x08080F10
#define CFG_RADIO_POWER_ADDRESS_STOP  0x08080F1F
/**
 * @brief Address of assert error message
 */
#define ASSERT_ERROR_MSG_ADDRESS 2

/**
 * @brief Configuration version
 * @details Version of configuration that will be
 * compatible with this application
 */
#define CFG_VERSION_D 118
#define CFG_VERSION_M 18

/**
 * @brief Address of configuration structure
 */
//#define CFG_FlASH_PAGE_ADDRESS ((uint32_t)0x0803D000)


/**
 * @brief Address of configuration crc low byte
 */
#define CFG_CRC_LOW_BYTE_ADDRESS (173)

/**
 * @brief Address of configuration crc high byte
 */
#define CFG_CRC_HIGH_BYTE_ADDRESS (172)

/**
 * @brief Configuration version
 * @details Version of configuration that will be
 * compatible with this application
 */

/**
 * @brief Low battery level [in ADC bits]
 */
#define SYS_LOW_BATTERY_LEVEL_D 2200
#define SYS_HIGH_BATTERY_LEVEL_D 2350

#define SYS_LOW_BATTERY_LEVEL_M 2550
#define SYS_HIGH_BATTERY_LEVEL_M 2780

/**
* @brief Priority of serial task
*/
#define serial_task_priority	(tskIDLE_PRIORITY + 1)

/**
* @brief Priority of radio task
*/
#define radio_task_priority	(tskIDLE_PRIORITY + 1)

/**
* @brief Priority of io ctrl task
*/
#define io_ctrl_task_priority	(tskIDLE_PRIORITY + 1)

/**
* @brief Priority of status ctrl task
*/
#define ctrl_task_priority	(tskIDLE_PRIORITY + 1)

/**
* @brief Priority of status cmd task
*/
#define cmd_task_priority	(tskIDLE_PRIORITY + 1)

/**
* @brief Size of data to transmitt via RF
*/
#define radio_rx_queue_size 20

/**
* @brief Size of data received from serial port
*/
#define serial_tx_queue_size 100

/**
* @brief Size of data to transfer through serial port
*/
#define serial_rx_queue_size 100

/**
* @brief Stack size for cmd task
*/
#define cmd_task_stack_size	(1024)

#define UART_recived 1
#define UART_clear 0

#endif /* CONFIG_H_ */
