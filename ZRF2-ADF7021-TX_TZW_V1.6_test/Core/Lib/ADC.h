/*
 * ADC.h
 *
 *  Created on: 28.08.2018
 *      Author: user
 */

#ifndef ADC_H_
#define ADC_H_

void ADC_init(void);
uint16_t ADC_read(uint8_t CH);
extern GPIO_TypeDef * analog_port_array[];
extern uint32_t analog_pins_array[];

#endif /* ADC_H_ */
