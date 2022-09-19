/*
 * ps2.h
 *
 *  Created on: April 14, 2022
 *      Author: Carson Miller
 */

#ifndef PS2_H_
#define PS2_H_

extern volatile int JS_X;
extern volatile int JS_Y;


void ADC14_config(void);
void ADC14_IRQHandler(void);

#endif /* PS2_H_ */
