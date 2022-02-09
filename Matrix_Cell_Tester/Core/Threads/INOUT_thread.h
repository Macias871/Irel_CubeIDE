#include <stdint.h>
#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "main.h"

void INOUT_task(void const * argument);
uint8_t h_adress(void);
void send_frame (void);
void Set_Out(uint8_t data);
