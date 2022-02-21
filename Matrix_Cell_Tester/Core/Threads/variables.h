/*
 * variables.h
 *
 *  Created on: 05.11.2021
 *      Author: Irel
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

typedef struct {
	uint8_t Adress;
	uint16_t frame_count;
	uint16_t frame_Tstamp;
	uint8_t OUT;
	uint8_t Mode;
	uint16_t crc;
	uint8_t do_it;
} rx_frame_;


typedef struct {
	uint8_t Adress;
	uint8_t State;
	uint16_t frame_count;
	uint16_t MADC;
	uint16_t CRC_sum;

} tx_frame_;

rx_frame_ RX_Frame;
tx_frame_ TX_Frame;

#define tx_frame_lenght 44

extern uint16_t IN_adc[8];


#endif /* VARIABLES_H_ */
