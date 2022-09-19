/*
 * play_game.h
 *
 *  Created on: Apr 29, 2022
 *      Author: carson, riley
 */

#include "end_song.h"
#include "initialize/ece353.h"


#ifndef INITIALIZE_PLAY_GAME_H_
#define INITIALIZE_PLAY_GAME_H_

/* Variable declarations*/
// not sure if we need this one or not
extern volatile int board[6][7];

/*Function declarations*/
void play_game_init(void);
bool spot_is_taken(int row, int col);
bool is_winning_piece(int row, int col);

#endif /* INITIALIZE_PLAY_GAME_H_ */
