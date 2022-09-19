/*
 * timer32.h
 *
 *  Created on: April 14, 2022
 *      Author: Carson Miller
 */

#ifndef TIMER32_H_
#define TIMER32_H_

#include "msp.h"
#include <stdbool.h>
#include <stdint.h>

extern volatile bool S2_pressed_70mS;
extern volatile bool update_LCD;

void T32_1_10mS_interrupt(void);
void T32_2_100mS_interrupt(void);
void T32_INT1_IRQHandler(void);
void T32_INT2_IRQHandler(void);

#endif /* TIMER32_H_ */
