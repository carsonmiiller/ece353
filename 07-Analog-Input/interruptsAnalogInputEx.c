/*
 * interrupts.c
 *
 *  Created on: Feb 20, 2022
 *      Author: carso
 */

#include "interrupts.h"

volatile uint32_t PS2_X_DIR = 0;

void T32_INT1_IRQHandler(){
    // start an ADC conversion
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

    // clear the timer interrupt
    TIMER32_1->INTCLR = BIT0;
}

void ADC14_IRQHandler(void){
    PS2_X_DIR = ADC14->MEM[0];
}
