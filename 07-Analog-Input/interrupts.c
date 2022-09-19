/*
 * interrupts.c
 *
 *  Created on: Aug 11, 2020
 *      Author: Joe Krachey
 */
#include "interrupts.h"

// Add a global variable that holds the most recent value of the X direction
volatile int JOYSTICK_X_DIR = 0;

// Add a global variable that holds the most recent value of the Y direction
volatile int JOYSTICK_Y_DIR = 0;


void T32_INT1_IRQHandler(void)
{
    // Start the ADC conversion
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

    // Clear the timer interrupt
    TIMER32_1->INTCLR = BIT0;

}

void ADC14_IRQHandler(void)
{
    // Read the X value
    JOYSTICK_X_DIR = ADC14->MEM[0];

    // Read the Y value
    JOYSTICK_Y_DIR = ADC14->MEM[1];
}
