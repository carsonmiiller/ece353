/*
 * timer32.c
 *
 *  Created on: April 14, 2022
 *      Author: Carson Miller
 */

#include "timer32.h"
#include "ece353.h"

/*
 * Configure Timer32_1 to generate an interrupt every 10mS
 */
void T32_1_10mS_interrupt(void){

    // stop the timer (reset all CONTROL register values to 0)
    TIMER32_1->CONTROL = 0;

    // set timer to be periodic and enable interrupts
    TIMER32_1->CONTROL = TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_SIZE;

    // set load register to 10mS
    // load value = (timer freq/prescalar) * desired period
    // load value = (24000000Hz / 1) * 0.01s = 240000
    TIMER32_1->LOAD = 240000;

    __enable_irq();
    NVIC_EnableIRQ(T32_INT1_IRQn);
    NVIC_SetPriority(T32_INT1_IRQn, 0);

    // start the timer
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;
}

/*
 * Configure Timer32_2 to generate an interrupt every 100mS
 */
void T32_2_100mS_interrupt(void){
    // stop the timer (reset all CONTROL register values to 0)
    TIMER32_2->CONTROL = 0;

    // set timer to be periodic and enable interrupts
    TIMER32_2->CONTROL = TIMER32_CONTROL_MODE   // periodic timer
                        | TIMER32_CONTROL_IE    // enable interrupt
                        | TIMER32_CONTROL_SIZE; // 32-bit counter

    // set load register to 10mS
    // load value = (timer freq/prescalar) * desired period
    // load value = (24000000Hz / 1) * 0.1s = 2400000
    TIMER32_2->LOAD = 2400000;

    __enable_irq();
    NVIC_EnableIRQ(T32_INT2_IRQn);
    NVIC_SetPriority(T32_INT2_IRQn, 0);

    // start the timer
    TIMER32_2->CONTROL |= TIMER32_CONTROL_ENABLE;
}
