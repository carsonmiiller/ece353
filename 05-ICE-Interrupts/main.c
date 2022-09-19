#include "msp.h"
#include "ece353.h"
#include "interrupts.h"
/**
 * main.c
 */
void main(void)
{
    bool led_state = false;
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer

    // initialize LED1 (function defined in in ece353.c)
    ece353_led1_init();

    // Initialize S1 to generate interrupts (function defined in interrupts.c)
    ice05_init_s1();

    while(1){
        // When 10 IO port interrupts have been detected, turn on LED1
        if(ALERT_S1_PRESSED_10){
            ALERT_S1_PRESSED_10 = false;
            led_state = !led_state;
            ece353_led1(led_state);
        }else{
            // do nothing
        }
    }
}
