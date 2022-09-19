/*
 * interrupts.c
 *
 *  Created on: May 3, 2022
 *      Author: cmiller77
 */

volatile int X_AXIS = 0;
volatile int Y_AXIS = 0;
volatile int Z_AXIS = 0;

/*
 * set global variables for things that happen every 10mS
 */
void T32_INT1_IRQHandler(void){
    ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC; // start an ADC14 conversion
    TIMER32_1->INTCLR = BIT0;   // clear the interrupt
}

/*
 * set global variables for things that happen every 100mS
 */
void T32_INT2_IRQHandler(void){
    TIMER32_2->INTCLR = BIT0; // clear interrupt
}

void ADC14_IRQHandler(void){
    // Read all accelerometer values into global variables
    X_AXIS = ADC14->MEM[0];
    Y_AXIS = ADC14->MEM[1];
    Z_AXIS = ADC14->MEM[2];
}
