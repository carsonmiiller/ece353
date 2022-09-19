/*
 * interrupts.h
 *
 *  Created on: Feb 17, 2022
 *      Author: cmiller77
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>
#include <stdint.h>
#include "msp.h"
#include "ece353.h"

extern volatile bool ALERT_S1_PRESSED;
extern volatile bool ALERT_S1_PRESSED_10;

void T32_INT1_IRQHandler();
void ice05_init_s1();
void xxxxxxx_IRQHandler();

#endif /* INTERRUPTS_H_ */
