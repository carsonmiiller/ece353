/*
 * main.c
 *
 *  Created on: April 14, 2022
 *      Author: Carson Miller
 *
 *  Description
 *  This file should only require you to comment out line 24 below when you are ready
 *  to test your own code.
 */

#include "msp.h"
#include "tic_tac_toe.h"

void main(void)
{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    lcd_init();

    // Comment this line out when you add your own code to
    // implement the tic tac toe game.
    //tic_tac_toe_example_board();

    // Reach infinite loop
    while(1){
        tic_tac_toe_play_game();
    }

}
