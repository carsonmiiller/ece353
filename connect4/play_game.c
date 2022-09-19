/*
 * play_game.c
 *
 *  Created on: Apr 29, 2022
 *      Author: carson, riley
 */
volatile int board[6][7];
/*
 * Plays a game of Connect 4.
 *
 * Returns when a winner has been decided.
 */
void play_game_init(void){
    // create empty board
    board = {{0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0}};
    int player1 = 1;
    int player2 = 2;
    int turn = player1;
    int game_over = 0;
    int winner = 0;
    int select_col = 0; // 

    while(!game_over){

        // check accelerometer for selection position
        select_col = get_position_accelerometer();
        // if s2 pressed, attempt to place piece
        if(ece353_MKII_S2()){
            if(turn==player1){
                // if piece placed successfully, change turn
                // if it's not placed successfully, nothing will happen
                if(place_piece(player1, select_col)){
                    turn = player2;
                }
            }   
            else{
                if(place_piece(player2, select_col)){
                    turn = player1;
                }
            }
        }
        // check ambient light sensor
        if(is_winning_piece()){
            winner = turn;
            game_over = 1;
        }
    }
    // do game over stuff here
    // play game over sound
    we_are_the_champions();
    while(!ece3533_MKII_S2()){}
}

/* This should ideally place a piece in the correct slot in a column.
    Returns 1 if successful placement, 0 otherwise
*/
int place_piece(player, col){
    int i;
    for(i=0;i<6;i++){
        // if we're in first row and its taken, then entire column is full
        if(i==0 && spot_is_taken(i, col)){
            return 0;
        }
        // if we're in empty last row, then we've reached the end
        else if(i==5 && !spot_is_taken(i, col)){
            board[i][col] = player;
            return 1;
        }
        // if current spot is empty and next spot down is taken, then this is valid spot to place
        else if(!spot_is_taken(i, col) && i!=5 && spot_is_taken(i+1, col)){
            board[i][col] = player;
            return 1;
        }
    }
    // if we get all the way through that without placing, then something went wrong. Return 0
    return 0;
}

int get_position_accelerometer(){
    int accell = 0;// ece353_accelerometer or whatever function()
    int max_accel = 100000; // whatever the max accelerometer value is 
    int pos1 = max_accel / 7;
    int pos2 = max_accel * 2 / 7;
    int pos3 = max_accel * 3 / 7;
    int pos4 = max_accel * 4 / 7;
    int pos5 = max_accel * 5 / 7;
    int pos6 = max_accel * 6 / 7;
    int pos7 = max_accel * 7 / 7;
    if (accell < pos1){
        return 0;
    }
    else if(accell<pos2){
        return 1;
    }
    else if(accell<pos3){
        return 2;
    }
    else if(accell<pos4){
        return 3;
    }
    else if(accell<pos5){
        return 4;
    }
    else if(accell<pos6){
        return 5;
    }
    else if(accell<pos7){
        return 6;
    }
}

/*
 * Returns whether or not a spot is taken
 *
 * Params :
 *      row - specifies the row (0 is bottom, 5 is top)
 *      col - specifies the column (0 is far left, 6 is far right)
 * Returns :
 *      true if spot is occupied by a piece
 *      false if spot is empty
 */
bool spot_is_taken(int row, int col){
    if(board[row][col] == 0)
        return false;
    return true;
}

/*
 * Tells whether the last placed piece wins the game for player
 *
 * Params :
 *      row - specifies the row (0 is bottom, 5 is top)
 *      col - specifies the column (0 is far left, 6 is far right)
 * Returns :
 *      true if game is over with this piece placement
 *      false if game continues
 */
bool is_winning_piece(int row, int col){
    // vertical line win
    if(board[row][col] == board[row-1][col] == board[row-2][col] == board[row-3][col])
        return true;
    // horizontal win 1
    if(board[row][col] == board[row][col+1] == board[row][col+2] == board[row][col+3])
        return true;
    // horizontal win 2
    if(board[row][col-1] == board[row][col] == board[row][col+1] == board[row][col+2])
        return true;
    // horizontal win 3
    if(board[row][col-2] == board[row][col-1] == board[row][col] == board[row][col+1])
        return true;
    // horizontal win 4
    if(board[row][col-3] == board[row][col-2] == board[row][col-1] == board[row][col])
        return true;
    // diagonal win 1
    if(board[row][col] == board[row+1][col+1] == board[row+2][col+2] == board[row+3][col+3])
        return true;
    // diagonal win 2
    if(board[row-1][col-1] == board[row][col] == board[row+1][col+1] == board[row+2][col+2])
        return true;
    // diagonal win 3
    if(board[row-2][col-2] == board[row-1][col-1] == board[row][col] == board[row+1][col+1])
        return true;
    // diagonal win 4
    if(board[row-3][col-3] == board[row-2][col-2] == board[row-1][col-1] == board[row][col])
        return true;
    // diagonal win 5
    if(board[row][col] == board[row-1][col+1] == board[row-2][col+2] == board[row-3][col+3])
        return true;
    // diagonal win 6
    if(board[row+1][col-1] == board[row][col] == board[row-1][col+1] == board[row-2][col+2])
        return true;
    // diagonal win 7
    if(board[row+2][col-2] == board[row+1][col-1] == board[row][col] == board[row-1][col+1])
        return true;
    // diagonal win 8
    if(board[row+3][col-3] == board[row+2][col-2] == board[row+1][col-1] == board[row][col])
        return true;
}
