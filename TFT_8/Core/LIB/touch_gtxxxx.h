#ifndef _TOUCH_GTXXXX_H
#define _TOUCH_GTXXXX_H

#define LCD_PIXEL_WIDTH  800
#define LCD_PIXEL_HEIGHT 480
#define CTP_ADDRESS      0xBA //0xBA or 0x28
#define CTP_MAX_TOUCH    1 //1-10
																		 
int32_t CTP_Init_Panel(void);
void debug_uart(char *string);
#define  LVGL_USED 0

extern int16_t pos_x;
extern int16_t pos_y;


#if  LVGL_USED==0
uint8_t CTP_read(uint16_t* x, uint16_t* y, uint8_t* pressed);
#else
#include "lvgl/lvgl.h"
uint8_t CTP_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
#endif

#endif /*_TOUCH_GTXXXX_H */
