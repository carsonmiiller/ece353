/*
 * ps2.c
 *
 *  Created on: April 14, 2022
 *      Author: Carson Miller
 */

#include "msp.h"
#include "ps2.h"
#include "ece353.h"

volatile int JS_X;
volatile int JS_Y;

/*
 * Config the ADC14 to:
 *      sample 12-bit samples
 *      use 16 clock pulses in pulsed sample mode
 *      convert both the X and Y signals using a sequence of channels
 *      generate a single interrupt after the Y channel
 */
void ADC14_config(void){
    ece353_ADC14_PS2_XY();
}


/*
 * Store the X and Y values of the joy stick into the global variable
 */
void ADC14_IRQHandler(void){
    // Read the X value
    JS_X = ADC14->MEM[0];

    // Read the Y value
    JS_Y = ADC14->MEM[1];
}


