#include <stdint.h>
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"

void INOUT_task(void const * argument);
uint8_t h_adress(void);
void send_frame (uint16_t frame_cnt, uint8_t mode);
#define ANALOG_SEND 1
#define STATE_SEND 2
