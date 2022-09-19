/*
 * accelerometer.c
 *
 *  Created on: May 3, 2022
 *      Author: cmiller77
 */
#include "accelerometer.h"
void accel_init(void){
    // all pins as inputs
    X_AXIS_PORT->DIR &= ~X_AXIS_PIN;
    Y_AXIS_PORT->DIR &= ~Y_AXIS_PIN;
    Z_AXIS_PORT->DIR &= ~Z_AXIS_PIN;

    // select primary function for pins
    X_AXIS_PORT->SEL0 |= X_AXIS_PIN;
    Y_AXIS_PORT->SEL0 |= Y_AXIS_PIN;
    Z_AXIS_PORT->SEL0 |= Z_AXIS_PIN;
    X_AXIS_PORT->SEL1 &= ~X_AXIS_PIN;
    Y_AXIS_PORT->SEL1 &= ~Y_AXIS_PIN;
    Z_AXIS_PORT->SEL1 &= ~Z_AXIS_PIN;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    // NEW -- Indicate that this is a sequence-of-channels.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02 | ADC14_CTL0_CONSEQ_1;

    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;

    // Associate the X direction analog signal with MEM[0] (A14)
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14;

    // Associate the Y direction analog signal with MEM[1] (A13)
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_13;

    // Associate the Z direction analog signal with MEM[2] (A11)
    // NEW -- Make sure to indicate this is the end of a sequence.
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_EOS;

    // Enable interrupts in the ADC AFTER a value is written into MEM[2].
    ADC14->IER0 = ADC14_IER0_IE2;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);

    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;
}
