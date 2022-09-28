/**
 * @file    radio_thread.hpp
 * @brief	Radio transmission control thread
 * @date    26-06-2012
 * @author	Adam Miotk
 */

#ifndef RADIO_THREAD_HPP_
#define RADIO_THREAD_HPP_

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"
#include "config.h"

extern xTaskHandle radio_task_handle;
extern xQueueHandle radio_tx_queue;

#define SYNC 0x55
#define STARTB 0x02;
#define STOPB 0x03;

/*
#define RADIO_RECIEVING 1
#define RADIO_RECIEVIED 2
#define RADIO_TRANSMITTING 3
#define RADIO_TRANSMITTED 4
*/


void Decode_RX_Packet();
void Code_TX_Packet();
void Search_channel(void);
uint16_t crc_update(uint16_t crc,uint8_t data);

void arr_set_bit(uint8_t * const tab, const uint16_t bit);
void arr_clr_bit(uint8_t * const tab, const uint16_t bit);


/**
 * @brief Control radio module task.
 * @param pvParameters
 */
void radio_task(void const * argument);

/**
 * @brief User variables setup
 * @details Realization of function to configure radio module basic parameters
 * like channel number or power of transmitting waves.
 * Configuration algorithm:
 * 1) Push STOP button.
 * 2) Press START and P3 / P4 buttons in the same time (keep pushing STOP).
 * 3) Now you can increment channel number / transmit power by pressing P2 button.
 * 4) To save selected values pull STOP button.
 * @param actual_channel new channel (if changed)
 * @param actual_power new power (if changed)
 */
void user_cfg_setup(
	uint8_t * const actual_channel,
	uint8_t * const actual_power
);

/**
 * @brief Realization of function to enable buzzer for a while
 * @details Function uses system delay mechanism.
 * @param buzzer_port - buzzer IO port
 * @param buzzer_pin - buzzer IO pin
 * @param beep_no - how many beeps we do
 * @param beep_time - time of buzzer on state
 * @param idle_time - time of buzzer off state
 * @param off_state - if 0 buzzer is enabled by high state and disabled by low state
 */
void usr_beep(
	GPIO_TypeDef * buzzer_port,
	const uint32_t buzzer_pin,
	const uint8_t beep_no,
	const uint32_t beep_time,
	const uint32_t idle_time,
	const uint8_t off_state
);
#endif /* RADIO_THREAD_HPP_ */
