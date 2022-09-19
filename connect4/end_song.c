/*
 * end_song.c
 *
 *  Created on: Apr 29, 2022
 *      Author: carso
 */
#include "initialize/buzzer.h"
#include "end_song.h"
#include "initialize/ece353.h"
/*
 * Plays the victory song: 'We Are The Champions' by Queen
 */
void we_are_the_champions(void){
    buzzer_on();
    // we are the champions
    set_buzzer_freq(D_note);
    ece353_T32_1_wait_500mS();
    ece353_T32_1_wait_500mS();
    set_buzzer_freq(C__note);
    ece353_T32_1_wait_500mS();
    set_buzzer_freq(D_note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(C__note);
    ece353_T32_1_wait_500mS();
    set_buzzer_freq(A_note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    // my friends
    set_buzzer_freq(F__note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(B_note);
    ece353_T32_1_wait_500mS();
    set_buzzer_freq(F__note);
    ece353_T32_1_wait_500mS();
    // and we'll keep on fighting
    set_buzzer_freq(A_note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(D_note);
    ece353_T32_1_wait_500mS();
    set_buzzer_freq(E_note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(F__note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(A_note);
    ece353_T32_1_wait_500mS();
    set_buzzer_freq(F__note);
    ece353_T32_1_wait_500mS();
    // 'til the end
    set_buzzer_freq(B_note);
    ece353_T32_1_wait_100mS();
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(C__note);
    ece353_T32_1_wait_100mS();
    set_buzzer_freq(B_note);
    ece353_T32_1_wait_500mS();
    buzzer_off();
}

