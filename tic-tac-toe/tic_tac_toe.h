/*
 * tic_tac_toe.h
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */
#ifndef __TIC_TAC_TOE_H__
#define __TIC_TAC_TOE_H__

#include <stdbool.h>
#include "lcd.h"
#include "ps2.h"
#include "timer32.h"
#include "tic_tac_toe_images.h"
#include "ece353.h"

#define SCREEN_X            132
#define SCREEN_Y            132

#define SCREEN_CENTER_COL    ((SCREEN_X/2)-1)
#define SCREEN_CENTER_ROW    ((SCREEN_Y/2)-1)

#define LINE_WIDTH          4
#define LINE_LENGTH         (SCREEN_X - 1)

#define SQUARE_SIZE         32

#define PADDING             2

#define LEFT_COL                      (SCREEN_CENTER_COL - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_COL                    (SCREEN_CENTER_COL)
#define RIGHT_COL                     (SCREEN_CENTER_COL + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_ROW                     (SCREEN_CENTER_ROW - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_ROW                    (SCREEN_CENTER_ROW)
#define LOWER_ROW                     (SCREEN_CENTER_ROW + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_HORIZONTAL_LINE_Y     (SCREEN_CENTER_ROW - (SQUARE_SIZE/2) - PADDING - LINE_WIDTH/2)
#define LOWER_HORIZONTAL_LINE_Y     (SCREEN_CENTER_ROW + (SQUARE_SIZE/2) + PADDING + LINE_WIDTH/2)

#define LEFT_HORIZONTAL_LINE_X      (SCREEN_CENTER_COL - (SQUARE_SIZE/2) - PADDING - LINE_WIDTH/2)
#define RIGHT_HORIZONTAL_LINE_X     (SCREEN_CENTER_COL + (SQUARE_SIZE/2) + PADDING + LINE_WIDTH/2)



/*******************************************************************************
* Function Name: tic_tac_toe_hw_init
********************************************************************************
* Summary: Initializes all the hardware resources required for tic tac toe game
*          (IO Pins, ADC14, Timer32_1, Timer32_2).
* Returns:
*  Nothing
*******************************************************************************/ 
void tic_tac_toe_hw_init(void);

/*******************************************************************************
* Function Name: tic_tac_toe_example_board
********************************************************************************
* Summary: Prints out an example of what the tic-tac-toe board looks like
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_example_board(void);

/*******************************************************************************
* Function Name: tic_tac_toe_play_game
********************************************************************************
* Summary: Enters the code that plays the tic_tac_toe game.  Once called, this
*          function should never return!
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_play_game(void);

void display_board(void);
void draw_square(int x);
bool is_active_square(int x);
bool is_claimed(int x);
void claim_square();
void move_active_square();
int check_win();
#endif
