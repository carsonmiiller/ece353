/*
 * interrupts.c
 *
 *  Created on: Feb 24, 2022
 *      Author: carso
 */


/*
 * interrupts.c
 *
 *  Created on: Aug 20, 2020
 *      Author: Joe Krachey
 */
#include "interrupts.h"
// Add a global variable that holds the most recent value of the X direction
volatile int JOYSTICK_X_DIR = 0;
// Add a global variable that informs the application that the Window Camparator
// had detected a change
volatile int WINDOW_COMP_CHANGE = 0;


void T32_INT1_IRQHandler(void){
    // Start the ADC conversion
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

    // Clear the timer interrupt
    TIMER32_1->INTCLR = BIT0;
}
void ADC14_IRQHandler(void){
    // set the global variable that informs the application that the Window Comparator
    // had detected a change
    WINDOW_COMP_CHANGE = ADC14_IFGR1_HIIFG | ADC14_IFGR1_LOIFG | ADC14_IFGR1_INIFG;

    // Determine if the HIIFG interrupt is active
    if (ADC14_IFGR1_HIIFG){
        // Clear interrupt flag
        ADC14->CLRIFGR1 = ADC14_CLRIFGR1_CLRHIIFG;

        // Turn off the HI interrupt
        ADC14->IER1 &= ~ADC14_IER1_HIIE;

        // Turn on LOW and IN interrupts
        ADC14->IER1 |= ADC14_IER1_INIE | ADC14_IER1_LOIE;
    }

    // Determine if the LOIFG interrupt is active
    if (ADC14_IFGR1_LOIFG){
        // Clear interrupt flag
        ADC14->CLRIFGR1 = ADC14_CLRIFGR1_CLRLOIFG;

        // Turn off the LOW interrupt
        ADC14->IER1 &= ~ADC14_IER1_LOIE;

        // Turn on HI and IN interrupts
        ADC14->IER1 |= ADC14_IER1_INIE | ADC14_IER1_HIIE;
    }

    // Determine if the INIFG interrupt is active
    if (ADC14_IFGR1_INIFG){
        // Clear interrupt flag
        ADC14->CLRIFGR1 = ADC14_CLRIFGR1_CLRINIFG;

        // Turn off the IN interrupt
        ADC14->IER1 &= ~ADC14_IER1_INIE;

        // Turn on LOW and HI interrupts
        ADC14->IER1 |= ADC14_IER1_LOIE | ADC14_IER1_HIIE;
    }

    // Read the X channel
    JOYSTICK_X_DIR = ADC14->MEM[0];

}
