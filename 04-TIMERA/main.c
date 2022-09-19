#include "msp.h"
#include "ece353.h"

#define PWM_FREQ    3000
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	int pwm_count = (int)(SystemCoreClock/PWM_FREQ) - 1; // 3.0K

	// configure sw1
	ece353_MKII_S1_Init();

	// configure TimerA0
	ece353_MKII_Buzzer_Init(pwm_count);

	while(1){
	    if(ece353_MKII_S1()){ // if sw1 is being pressed, turn the buzzer on
	        // only turn the buzzer on if its current status is off
	        if(ece353_MKII_Buzzer_Run_Status() == false){
	            ece353_MKII_Buzzer_On();
	        }
	    }else{ // sw1 is not pressed, so turn the buzzer off
	        ece353_MKII_Buzzer_Off();
	    }
	}
}
