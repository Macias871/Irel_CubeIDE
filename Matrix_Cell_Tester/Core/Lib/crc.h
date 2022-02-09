/*
 * crc.h
 *
 *  Created on: 08.11.2021
 *      Author: Irel
 */

#ifndef CRC_H_
#define CRC_H_

uint16_t crc_update(uint16_t crc,uint8_t data);
uint16_t calc_crc(uint8_t *str, uint8_t len);
uint16_t hexStr2Arr(unsigned char* out, const char* in, size_t out_len_max);
uint8_t* datahex(char* string);
#endif /* CRC_H_ */
