#include "msp.h"
#include "ece353.h"
/**
 * main.c
 */
void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // stop watchdog timer
    // Initialize Button1
    ece353_button1_init();
    // Initialize LED1
    ece353_led1_init();

    while(1){
        // Wait for the button to be pressed
        ece353_button1_wait_for_press();
        // Turn LED On
        ece353_led1(true);
        // Wait for button to be released
        while(ece353_button1() == true){
            // busy wait
        }
        // Turn LED Off
        ece353_led1(false);
    }
}
