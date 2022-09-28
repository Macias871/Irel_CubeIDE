/**
 * @file    config.h
 * @brief	System configuration
 * @date    22-06-2012
 * @author	Adam Miotk
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#include "stm32l1xx_hal.h"
#include "cmsis_os.h"



#define RX_FRAME_BLEN 22
#define TX_FRAME_BLEN 22

#define RX_DISCONNECT_TIME 20U

/**
* @brief Size of data received from serial port
*/
#define serial_tx_queue_size 100

/**
* @brief Size of data to transfer through serial port
*/
#define serial_rx_queue_size 200

/**
 * @brief Address of configuration structure
 */
#define EEPROM_PAGE_ADDRESS ((uint32_t)0x8080C00)	//3bajt eeprom


/**
* @brief Priority of serial task
*/
#define usr_serial_task_priority	(tskIDLE_PRIORITY + 2)

/**
* @brief Priority of radio task
*/
#define usr_radio_task_priority	(tskIDLE_PRIORITY + 2)

/**
* @brief Priority of io ctrl task
*/
#define usr_io_ctrl_task_priority	(tskIDLE_PRIORITY + 2)

/**
* @brief Priority of ctrl task
*/
#define usr_ctrl_task_priority	(tskIDLE_PRIORITY + 2)

/**
* @brief Priority of cmd task
*/
#define usr_cmd_task_priority	(tskIDLE_PRIORITY + 2)

/**
* @brief Stack size for cmd task
*/
#define usr_cmd_task_stack_size	(1024)
#define CFG_VERSION 51

#endif /* CONFIG_H_ */
