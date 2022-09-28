
#ifndef RADIO_THREAD_HPP_
#define RADIO_THREAD_HPP_

#include "stm32l1xx_hal.h"
#include "cmsis_os.h"

extern xTaskHandle radio_task_handle;
extern xQueueHandle radio_tx_queue;
#define WAIT_TX 2
#define WAIT_RX 3
#define SET_ 1
#define RESET_ 0
#define SYNC 0x55
#define STARTB 0x02;
#define STOPB 0x03;

uint8_t tab_chk_bit(uint8_t * const tab, const uint16_t bit);
void SEND_Serial(uint8_t *PACKET, uint8_t Size);
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
	const uint8_t off_state,
	const uint8_t led
);

uint16_t crc_update(
	uint16_t crc,
	uint8_t data
);

void Code_TX_Packet();
uint8_t Decode_RX_Packet();

void chk_rf_buffers(void);
#endif /* RADIO_THREAD_HPP_ */
