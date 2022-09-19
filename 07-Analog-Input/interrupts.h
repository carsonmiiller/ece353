/*
 * interrupts.h
 *
 *  Created on: Feb 21, 2022
 *      Author: cmiller77
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdbool.h>
#include <stdint.h>
#include "msp.h"
#include "ece353.h"

// Add a global variable that holds the most recent value of the X direction
extern volatile int JOYSTICK_X_DIR;

// Add a global variable that holds the most recent value of the Y direction
extern volatile int JOYSTICK_Y_DIR;

void T32_INT1_IRQHandler(void);
void ADC14_IRQHandler(void);


#endif /* INTERRUPTS_H_ */
