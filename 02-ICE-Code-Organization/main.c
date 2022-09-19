#include "msp.h"
#include "ece353.h"

/**
 * main.c
 */
void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	void ece353_led1_init();
	void ece353_button1_init();
	int count = 0; // tracks which RBG LED is on, default to OFF

	while(1){
	    if(ece353_button1()){ // if button1 is pressed
	        while(1){ // wait for button2 to be pressed
	            if(ece353_button2()){ // if button2 is pressed
	                break;
	            }
	        }
	        if(count == 0){ // if RGB LED is off
	            // turn only red on
	            ece353_rgb(true, false, false);
	            count = 1;
	        }
	        else if(count == 1){ // if RBG LED is red
	            // turn only green on
	            ece353_rgb(false, true, false);
	            count = 2;
	        }
	        else if(count == 2){ // if RBG LED is green
	            // turn only blue on
	            ece353_rgb(false, false, true);
	            count = 3;
	        }
	        else if(count == 3){ // if RBG LED is blue
	            // turn OFF
	            ece353_rgb(false, false, false);
	            count = 0;
	        }
	    }
	}
}
