/*
 * tic_tac_toe.c
 *
 *  Created on: Oct 5, 2020
 *      Author: YOUR NAME
 */

#include "tic_tac_toe.h"
#define VOLT_0P60 ((int)(0.6/(3.3/4096)))
#define VOLT_2P70 ((int)(2.7/(3.3/4096)))

extern volatile bool update_LCD;
extern volatile bool S2_pressed_70mS;
extern volatile int JS_X;
extern volatile int JS_Y;

/*******************************************************************************
* Function Name: tic_tac_toe_hw_init
********************************************************************************
* Summary: Initializes all the hardware resources required for tic tac toe game
*          (IO Pins, ADC14, Timer32_1, Timer32_2).
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_hw_init(void){
    T32_1_10mS_interrupt();
    T32_2_100mS_interrupt();
    ADC14_config();
}

/*******************************************************************************
* Function Name: tic_tac_toe_example_board
********************************************************************************
* Summary: Prints out an example of what the tic-tac-toe board looks like
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_example_board(void)
{
    // Horizontal Lines
    lcd_draw_rectangle(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE);
    lcd_draw_rectangle(SCREEN_CENTER_COL,LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE);

    //Vertical Lines
    lcd_draw_rectangle(LEFT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH,LCD_COLOR_BLUE);
    lcd_draw_rectangle(RIGHT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH,LINE_LENGTH,LCD_COLOR_BLUE);

    // Top Row
    lcd_draw_image(LEFT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_RED,LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL,UPPER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL,UPPER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_GREEN,LCD_COLOR_BLACK);

    // Center Row
    lcd_draw_image(LEFT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_BLUE,LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL,CENTER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_O,LCD_COLOR_ORANGE,LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL,CENTER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_X,LCD_COLOR_CYAN,LCD_COLOR_BLACK);

    // Lower Row
    lcd_draw_image(LEFT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_MAGENTA,LCD_COLOR_BLACK);
    lcd_draw_image(CENTER_COL,LOWER_ROW,X_WIDTH,X_HEIGHT,Bitmaps_X,LCD_COLOR_GRAY,LCD_COLOR_BLACK);
    lcd_draw_image(RIGHT_COL,LOWER_ROW,O_WIDTH,O_HEIGHT,Bitmaps_O,LCD_COLOR_BROWN,LCD_COLOR_BLACK);
}


    static int winner = -1;
    static int board[9] = {1, 2, 3,
                           4, 5, 6,
                           7, 8, 9};
    static int active_square = 5;   // active_square starts in middle
    static int active_player = 10; // 10 for X, 0 for O, always starts with X

/*******************************************************************************
* Function Name: tic_tac_toe_play_game
********************************************************************************
* Summary: Enters the code that plays the tic_tac_toe game.  Once called, this
*          function should never return!
* Returns:
*  Nothing
*******************************************************************************/
void tic_tac_toe_play_game(void){
    // never return
    tic_tac_toe_hw_init();
    while(1){
        // while game isnt over, continue playing
        while(check_win() == -1){
            move_active_square();
            claim_square();
            if(update_LCD)
                display_board();
        }

        // END OF GAME
        // tie
        if(check_win() == 0){
            lcd_tie();
        }
        // winner
        else if(check_win() == 1){
            // x wins
            if(winner == 10)
                lcd_X_wins();
            // o wins
            else if(winner == 0)
                lcd_O_wins();
        }

        // waiting for S2 button press to start next game
        while(!S2_pressed_70mS){
            winner = -1;
            board[0] = 1;
            board[1] = 2;
            board[2] = 3;
            board[3] = 4;
            board[4] = 5;
            board[5] = 6;
            board[6] = 7;
            board[7] = 8;
            board[8] = 9;
            active_square = 5;
            active_player = 10;
        }
    }
}

/*
 * Displays the board as it is updated by play
 */
void display_board(){
    // ALWAYS DRAW THESE LINES
    // Horizontal Lines
    lcd_draw_rectangle(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE);
    lcd_draw_rectangle(SCREEN_CENTER_COL,LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH,LINE_WIDTH,LCD_COLOR_BLUE);
    //Vertical Lines
    lcd_draw_rectangle(LEFT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH,LCD_COLOR_BLUE);
    lcd_draw_rectangle(RIGHT_HORIZONTAL_LINE_X,SCREEN_CENTER_ROW, LINE_WIDTH,LINE_LENGTH,LCD_COLOR_BLUE);

    // DRAW EACH SQUARE ACCORDING TO IT'S CURRENT STATE
    draw_square(1);
    draw_square(2);
    draw_square(3);
    draw_square(4);
    draw_square(5);
    draw_square(6);
    draw_square(7);
    draw_square(8);
    draw_square(9);
}

/*
 * Draws all squares according to their state
 */
void draw_square(int x){
    // square 1
    if(!is_claimed(1) && !is_active_square(1)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(LEFT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(1) && is_active_square(1) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(LEFT_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(1) && is_active_square(1) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(LEFT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(1) && is_active_square(1) && board[1] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(LEFT_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(1) && is_active_square(1) && board[1] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(LEFT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(1) && !is_active_square(1) && board[1] == 10) // claimed by X but not active
        lcd_draw_image(LEFT_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(LEFT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background
    
    // square 2
    if(!is_claimed(2) && !is_active_square(2)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(CENTER_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(2) && is_active_square(2) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(CENTER_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(2) && is_active_square(2) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(CENTER_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(2) && is_active_square(2) && board[2] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(CENTER_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(2) && is_active_square(2) && board[2] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(CENTER_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(2) && !is_active_square(2) && board[2] == 10) // claimed by X but not active
        lcd_draw_image(CENTER_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(CENTER_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 3
    if(!is_claimed(3) && !is_active_square(3)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(RIGHT_COL, UPPER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(3) && is_active_square(3) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(RIGHT_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(3) && is_active_square(3) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(RIGHT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(3) && is_active_square(3) && board[3] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(RIGHT_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(3) && is_active_square(3) && board[3] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(RIGHT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(3) && !is_active_square(3) && board[3] == 10) // claimed by X but not active
        lcd_draw_image(RIGHT_COL, UPPER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(RIGHT_COL, UPPER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 4
    if(!is_claimed(4) && !is_active_square(4)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(LEFT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(4) && is_active_square(4) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(LEFT_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(4) && is_active_square(4) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(LEFT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(4) && is_active_square(4) && board[4] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(LEFT_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(4) && is_active_square(4) && board[4] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(LEFT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(4) && !is_active_square(4) && board[4] == 10) // claimed by X but not active
        lcd_draw_image(LEFT_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(LEFT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 5
    if(!is_claimed(5) && !is_active_square(5)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(CENTER_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(5) && is_active_square(5) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(CENTER_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(5) && is_active_square(5) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(CENTER_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(5) && is_active_square(5) && board[5] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(CENTER_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(5) && is_active_square(5) && board[5] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(CENTER_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(5) && !is_active_square(5) && board[5] == 10) // claimed by X but not active
        lcd_draw_image(CENTER_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(CENTER_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 6
    if(!is_claimed(6) && !is_active_square(6)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(RIGHT_COL, CENTER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(6) && is_active_square(6) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(RIGHT_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(6) && is_active_square(6) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(RIGHT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(6) && is_active_square(6) && board[6] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(RIGHT_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(6) && is_active_square(6) && board[6] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(RIGHT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(6) && !is_active_square(6) && board[6] == 10) // claimed by X but not active
        lcd_draw_image(RIGHT_COL, CENTER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(RIGHT_COL, CENTER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 7
    if(!is_claimed(7) && !is_active_square(7)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(LEFT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(7) && is_active_square(7) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(LEFT_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(7) && is_active_square(7) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(LEFT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(7) && is_active_square(7) && board[7] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(LEFT_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(7) && is_active_square(7) && board[7] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(LEFT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(7) && !is_active_square(7) && board[7] == 10) // claimed by X but not active
        lcd_draw_image(LEFT_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(LEFT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 8
    if(!is_claimed(8) && !is_active_square(8)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(CENTER_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(8) && is_active_square(8) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(CENTER_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(8) && is_active_square(8) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(CENTER_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(8) && is_active_square(8) && board[8] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(CENTER_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(8) && is_active_square(8) && board[8] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(CENTER_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(8) && !is_active_square(8) && board[8] == 10) // claimed by X but not active
        lcd_draw_image(CENTER_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(CENTER_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background

    // square 9
    if(!is_claimed(9) && !is_active_square(9)) // if it hasn't been claimed and isn't active
        lcd_draw_rectangle(RIGHT_COL, LOWER_ROW, SQUARE_SIZE, SQUARE_SIZE, LCD_COLOR_BLACK); // black square
    else if(!is_claimed(9) && is_active_square(9) && active_player == 10) // hasn't been claimed but is active (X is active_player)
        lcd_draw_image(RIGHT_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black X on green background
    else if(!is_claimed(9) && is_active_square(9) && active_player == 0) // hasn't been claimed but is active (O is active_player)
        lcd_draw_image(RIGHT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_GREEN); // black O on green background
    else if(is_claimed(9) && is_active_square(9) && board[9] == 10) // has been claimed and is active (previously claimed by X)
        lcd_draw_image(RIGHT_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_BLACK, LCD_COLOR_RED); // black X on red background
    else if(is_claimed(9) && is_active_square(9) && board[9] == 0) // has been claimed and is active (previously claimed by O)
        lcd_draw_image(RIGHT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_BLACK, LCD_COLOR_RED); // black O on red background
    else if(is_claimed(9) && !is_active_square(9) && board[9] == 10) // claimed by X but not active
        lcd_draw_image(RIGHT_COL, LOWER_ROW, X_WIDTH, X_HEIGHT, Bitmaps_X, LCD_COLOR_YELLOW, LCD_COLOR_BLACK); // yellow X on black background
    else // claimed by O but not active
        lcd_draw_image(RIGHT_COL, LOWER_ROW, O_WIDTH, O_HEIGHT, Bitmaps_O, LCD_COLOR_CYAN, LCD_COLOR_BLACK); // cyan O on black background
}

/*
 * Returns true if square is active, false otherwise
 */
bool is_active_square(int x){
    if(x == active_square)
        return true;
    return false;
}

/*
 * Returns true if square is claimed, false otherwise
 */
bool is_claimed(int x){
    if(board[x] == 10 || board[x] == 0)
        return true;
    return false;
}

/*
 * If available, allows user to claim their active square and changes active player
 * otherwise, does nothing
 */
void claim_square(){
    // if active_square not claimed and button is pressed
    if(board[active_square] != 10 && board[active_square] != 0 && S2_pressed_70mS){
        board[active_square] = active_player; // square is claimed
        active_player = (active_player + 10) % 20; // player is changed
    }
}

/*
 * Moves the actve square depending on joystick input
 */
void move_active_square(){
    if(active_square == 1){
        if(JS_X > VOLT_2P70)      // right
            active_square = 2;
        else if(JS_X < VOLT_0P60) // left
            active_square = 3;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 7;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 4;
    }
    else if(active_square == 2){
        if(JS_X > VOLT_2P70)      // right
            active_square = 3;
        else if(JS_X < VOLT_0P60) // left
            active_square = 1;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 8;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 5;
    }
    else if(active_square == 3){
        if(JS_X > VOLT_2P70)      // right
            active_square = 1;
        else if(JS_X < VOLT_0P60) // left
            active_square = 2;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 9;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 6;
    }
    else if(active_square == 4){
        if(JS_X > VOLT_2P70)      // right
            active_square = 5;
        else if(JS_X < VOLT_0P60) // left
            active_square = 6;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 1;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 7;
    }
    else if(active_square == 5){
        if(JS_X > VOLT_2P70)      // right
            active_square = 6;
        else if(JS_X < VOLT_0P60) // left
            active_square = 4;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 2;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 8;
    }
    else if(active_square == 6){
        if(JS_X > VOLT_2P70)      // right
            active_square = 4;
        else if(JS_X < VOLT_0P60) // left
            active_square = 5;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 3;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 9;
    }
    else if(active_square == 7){
        if(JS_X > VOLT_2P70)      // right
            active_square = 8;
        else if(JS_X < VOLT_0P60) // left
            active_square = 9;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 4;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 1;
    }
    else if(active_square == 8){
        if(JS_X > VOLT_2P70)      // right
            active_square = 9;
        else if(JS_X < VOLT_0P60) // left
            active_square = 7;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 5;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 2;
    }
    else if(active_square == 9){
        if(JS_X > VOLT_2P70)      // right
            active_square = 7;
        else if(JS_X < VOLT_0P60) // left
            active_square = 8;
        else if(JS_Y > VOLT_2P70) // up
            active_square = 6;
        else if(JS_Y < VOLT_0P60) // down
            active_square = 3;
    }
}

/*
 * Checks for a win and sets the winner variable to 10 for X winning, 0 for O winning, or -1 for tie, depending on winner
 * Returns 1 if there's a winner, 0 if tie, and -1 if game not finished
 */
int check_win(){
    if (board[0] == board[1] && board[1] == board[2]){
        winner = board[0];
        return 1;
    }
    else if (board[3] == board[4] && board[4] == board[5]){
        winner = board[3];
        return 1;
    }
    else if (board[6] == board[7] && board[7] == board[8]){
        winner = board[6];
        return 1;
    }
    else if (board[0] == board[3] && board[3] == board[6]){
        winner = board[0];
        return 1;
    }
    else if (board[1] == board[4] && board[4] == board[7]){
        winner = board[1];
        return 1;
    }
    else if (board[2] == board[5] && board[5] == board[8]){
        winner = board[2];
        return 1;
    }
    else if (board[0] == board[4] && board[4] == board[8]){
        winner = board[0];
        return 1;
    }
    else if (board[2] == board[4] && board[4] == board[6]){
        winner = board[2];
        return 1;
    }
    else if (board[0] != 1 && board[1] != 2 && board[2] != 3 && board[3] != 4 && board[4] != 5 && board[5] != 6 && board[6] != 7 && board[7] != 8 && board[8] != 9){
        winner = -1;
        return 0; // tie
    }
    else{
        return -1;
    }
}
