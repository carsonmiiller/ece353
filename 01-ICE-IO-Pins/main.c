#include "msp.h"


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P1->DIR &= ~BIT1; // initialize Button 1 to 0 (input)
	P1->DIR &= ~BIT4; // initialize Button 2 to 0 (input)

	P1->REN |= BIT1; // enable Button 1 pullup/down resistor
	P1->REN |= BIT4; // enable Button 2 pullup/down resistor

	P1->OUT |= BIT1; // pullup selected
	P1->OUT |= BIT4; // pullup selected

	P2->DIR |= BIT2; // RBGLED_BLUE initialized to output
    P2->DIR |= BIT1; // RBGLED_GREEN initialized to output
    P2->DIR |= BIT0; // RBGLED_RED initialized to output

    P2->OUT &= ~BIT2; // RBGLED_BLUE initialized to off
    P2->OUT &= ~BIT1; // RBGLED_GREEN initialized to off
    P2->OUT &= ~BIT0; // RBGLED_RED initialized to off

    int count = 3;

    while(1){
        while(~P1->IN & BIT1){ // enter this while loop when Button 1 is pressed
            if(~P1->IN & BIT4){ // if Button 2 is pressed

                if(count == 0){ // if RBGLED_RED is on
                    P2->OUT = 0; // turn RBGLED_RED off
                    P2->OUT |= BIT1; // turn RBGLED_GREEN on
                    count++;
                } else if(count == 1){ // if RBGLED_GREEN is on
                    P2->OUT = 0; // turn RBGLED_GREEN off
                    P2->OUT |= BIT2; // turn RBGLED_BLUE on
                    count++;
                } else if(count == 2){ // if RBGLED_BLUE is on
                    P2->OUT = 0; // turn RBGLED_BLUE off
                    count++;
                } else { // if none are on
                    P2->OUT |= BIT0; // turn RBGLED_RED on
                    count = 0;
                }
            }
        }
    }

}
