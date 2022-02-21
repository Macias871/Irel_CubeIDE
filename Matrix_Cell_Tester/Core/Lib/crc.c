/*
 * crc.c
 *
 *  Created on: 08.11.2021
 *      Author: Irel
 */


#include "cmsis_os.h"
#include "stm32l1xx_hal.h"
#include "crc.h"


uint16_t calc_crc(uint8_t *str, uint8_t len)
{


	uint16_t loop_counter =0;
	uint16_t cfg_crc = 0xFFFF;
	uint8_t byte = 0;
	for (loop_counter = 0; loop_counter < len; loop_counter++) {
		byte = str[loop_counter];
		cfg_crc = crc_update(cfg_crc, byte);


	}
	return cfg_crc;
}


uint16_t crc_update(uint16_t crc,uint8_t data)
{
    data ^= (uint8_t) (crc & 0xFF);
    data ^= data << 4;
    return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}



uint8_t* datahex(char* string) {

    if(string == NULL)
       return NULL;

    size_t slength = strlen(string);
    if((slength % 2) != 0) // must be even
       return NULL;

    size_t dlength = slength / 2;

    uint8_t* data = malloc(dlength);
    memset(data, 0, dlength);

    size_t index = 0;
    while (index < slength) {
        char c = string[index];
        int value = 0;
        if(c >= '0' && c <= '9')
          value = (c - '0');
        else if (c >= 'A' && c <= 'F')
          value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
          value = (10 + (c - 'a'));
        else {
          free(data);
          return NULL;
        }

        data[(index/2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}


uint16_t hexStr2Arr(unsigned char* out, const char* in, size_t out_len_max)
{
    if (!out_len_max)
        out_len_max = 2147483647; // INT_MAX

    const uint16_t in_len = strnlen(in, out_len_max * 2);
    if (in_len % 2 != 0)
        return -1; // error, in str len should be even

    // calc actual out len
    const int out_len = out_len_max < (in_len / 2) ? out_len_max : (in_len / 2);

    for (int i = 0; i < out_len; i++) {
        char ch0 = in[2 * i];
        char ch1 = in[2 * i + 1];
        uint8_t nib0 = (ch0 & 0xF) + (ch0 >> 6) | ((ch0 >> 3) & 0x8);
        uint8_t nib1 = (ch1 & 0xF) + (ch1 >> 6) | ((ch1 >> 3) & 0x8);
        out[i] = (nib0 << 4) | nib1;
    }
    return out_len;
}
