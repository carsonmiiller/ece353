#include "ece353.h"

/* ***************************************************
 * Initialize hardware resources used to control LED1
 *****************************************************/
void ece353_led1_init(void){
    // set direction as an output
    P1->DIR |= BIT0;
    // turn off LED as default
    P1->OUT &= ~BIT0;
}

/*****************************************************
 * Initialize hardware resources used to control Button1
 *****************************************************/
void ece353_button1_init(void){
    // set direction as an input
    P1->DIR &= ~BIT1;
    // enable internal resistor
    P1->REN |= BIT1;
    // select pull-up resistor
    P1->OUT |= BIT1;
}

/*****************************************************
 * Turn LED1 ON/Off.
 *
 * Parameters
 *  on: if true,  turn LED on
 *      if false, turn LED off
 *****************************************************/
void ece353_led1(bool on){
    if(on)
        P1->OUT |= BIT0; // turn LED on
    else
        P1->OUT &= ~BIT0; // turn LED off
}

/*****************************************************
 * Returns if Button1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_button1(void){
    if((P1->IN & BIT1) == 0) // if someone is pushing the button
        return true;
    else // if no one is pushing the button
        return false;
}



//****************************************************
//****************************************************
// 02-ICE-Code-Organization
//****************************************************
//****************************************************

/*****************************************************
 * Initialize hardware resources used to control RGBLED
 *****************************************************/
void ece353_rgb_init(void){
    // set direction of RBG to output
    P2->DIR |= BIT0;
    P2->DIR |= BIT1;
    P2->DIR |= BIT2;

    // turn off RGB LED as default
    P2->OUT &= ~BIT0;
    P2->OUT &= ~BIT1;
    P2->OUT &= ~BIT2;
}

/*****************************************************
 * Turn RGBLED ON/Off.
 *
 * Parameters
 *  red_on      :   if true,  turn RGBLED.RED on
 *                  if false, turn RGBLED.RED off
 *  green_on    :   if true,  turn RGBLED.GREEN on
 *                  if false, turn RGBLED.GREEN off
 *  blue_on     :   if true,  turn RGBLED.BLUE on
 *                  if false, turn RGBLED.BLUE off
 *****************************************************/
void ece353_rgb(bool red_on, bool green_on, bool blue_on){
    if(red_on)
        P2->OUT |= BIT0; // turn red on
    else
        P2->OUT &= ~BIT0; // turn red off
    if(green_on)
            P2->OUT |= BIT1; // turn green on
        else
            P2->OUT &= ~BIT1; // turn green off
    if(blue_on)
            P2->OUT |= BIT2; // turn blue on
        else
            P2->OUT &= ~BIT2; // turn blue off
}

/*****************************************************
 * Initialize hardware resources used to control Button2
 *****************************************************/
void ece353_button2_init(void){
    // set direction as an input
    P1->DIR &= ~BIT4;
    // enable internal resistor
    P1->REN |= BIT4;
    // select pull-up resistor
    P1->OUT |= BIT4;
}

/*****************************************************
 * Returns if Button2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button2 is pressed
 *      false   :   Button2 is NOT pressed
 *****************************************************/
bool ece353_button2(void){
    if((P1->IN & BIT4) == 0) // if someone is pushing the button
        return true;
    else // if no one is pushing the button
        return false;
}

/*****************************************************
 * Busy waits for 100mS and then returns.
 *
 * Timer32_1 MUST be configured as a 16-bit timer.
 * Assume that the MCU clock runs at 3MHz.  You will
 * need to use a pre-scalar in order to achieve a delay
 * of 100mS.
 *
 * Parameters:
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_wait_100mS(void){
    // stop the timer
    TIMER32_1->CONTROL = 0;

    // set timer to be 16-bit timer
    TIMER32_1->CONTROL = TIMER32_CONTROL_ONESHOT;

    // load value = (timer freq/prescalar) * desired period

    // set prescalar to divide by 16
    TIMER32_1->CONTROL |= TIMER32_CONTROL_PRESCALE_1;

    // set the load register
    TIMER32_1->LOAD = 18750;

    // start the timer
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE;

    // wait until it reaches 0
    while(TIMER32_1->VALUE != 0){
        // timer is still counting...
    }
}

/*****************************************************
 * Debounces Button1 using Timer32_1.
 * This function does not return until Button 1 has
 * been pressed for a minimum of 5 seconds.
 *
 * Waiting 5 Seconds will require you to call
 * ece353_T32_1_wait_100mS multiple times.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_button1_wait_for_press(void){
    // counter for 5s
    int count = 0;
    while(1){
        while(!ece353_button1()){
            // waiting for button1 to be pressed
        }
        // once button1 is pressed, start counting to 5s
        while(1){
            // keep checking button1
            if(ece353_button1()){
                // wait 100ms in between checks
                ece353_T32_1_wait_100mS();
                // increment count to keep track of how many 100ms waits have executed
                count++;
            } else {
                break; // if button1 is released before 5s, break loop and begin waiting again
            }
            if(count == 50){ // if count gets to 50, this means the button has been held for 5s
                return;
            }
        }
    }
}

/*****************************************************
 * Initialize the hardware resources used to control S1
 * on the MKII
 *****************************************************/
void ece353_MKII_S1_Init(void){
    // configure as input
    P5->DIR &= ~BIT1;

    // Enable resistor
    // P5->REN |= BIT1;

    // Resistor as a pull-up resistor
    // P5->OUT |= BIT1;
}

/*****************************************************
 * Initialize the hardware resources used to control S2
 * on the MKII
 *****************************************************/
void ece353_MKII_S2_Init(void){
    // configure as input
    P3->DIR &= ~BIT5;

    // Enable resistor
    // P3->REN |= BIT5;

    // Resistor as a pull-up resistor
    // P3->OUT |= BIT5;
}

/*****************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is not pressed
 *****************************************************/
bool ece353_MKII_S1(void){
    if((P5->IN & BIT1) == 0){
        return true;
    }else{
        return false;
    }
}

/*****************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button2 is pressed
 *      false   :   Button2 is not pressed
 *****************************************************/
bool ece353_MKII_S2(void){
    if((P3->IN & BIT5) == 0){
        return true;
    }else{
        return false;
    }
}


/*****************************************************
 * Sets the PWM period of the Buzzer. The duty cycle
 * will be set to 50%
 *
 * Parameters
 *      ticks_period    :   Period of PWM pulse
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_Buzzer_Init(int ticks_period){
    // Set P2.7 to be a GPIO OUTPUT Pin
    P2->DIR |= BIT7;

    // the TIMERA PWM controller will control the buzzer on the MKII
    // P2.7 <--> TA0.4
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    // Turn off TA0
    TIMER_A0->CTL = 0;

    // set the period of the timer
    TIMER_A0->CCR[0] = ticks_period - 1;

    // configure Buzzer duty cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period / 2) - 1;

    // configure TA0.4 for RESET/SET mode
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

    // Select the master clock as the timer source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
}

/*****************************************************
 * Turns the Buzzer on
 *
 * Parameters
 *      None
 *
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_Buzzer_On(void){
    // clear the current mode control bits
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;

    // set mode control to up and clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
}

/*****************************************************
 * Turns the Buzzer off
 *
 * Parameters
 *      None
 *
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_Buzzer_Off(void){
    // turn off the timer
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;
}

/*****************************************************
 * Check Buzzer Run Status
 *
 * Parameters
 *      None
 *
 * Returns
 *      True if TimerA0 is On.
 *      False if TimerA0 is Off
 *****************************************************/
bool ece353_MKII_Buzzer_Run_Status(void){
    if((TIMER_A0->CTL & TIMER_A_CTL_MC_MASK) == TIMER_A_CTL_MC__STOP){
        return false;
    }else{
        return true;
    }
}

//*****************************************************************************
//*****************************************************************************
// ICE 04 - PWMing MKII tri-color LED.
//*****************************************************************************
//*****************************************************************************

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(bool en_primary_function)
{

    // Complete the comments below to identify which pins
    // control which LEDs.
    //
    // Replace a and c with the correct port number
    // Replace b and d with the correct pin numbers.
    // RED      : P2.6
    // GREEN    : Pa.b
    // BLUE     : Pc.d

    // ADD CODE that configures the RED, GREEN, and
    // BLUE LEDs to be outputs



    // ADD CODE that selects the Primary module function
    // for all 3 pins
    if(en_primary_function)
    {

    }

}

/*****************************************************
 * Sets the PWM levels for the MKII RGBLED
 *
 * Parameters
 *      ticks_period    :   Period of PWM Pulse
 *      red_num         :   RED RGB Number
 *      green_num       :   GREEN RGB Number
 *      blue_num        :   BLUE RGB Number
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_PWM(
        uint16_t ticks_period,
        uint16_t red_num,
        uint16_t green_num,
        uint16_t blue_num
)
{
    // This code converts the HTML color codes into a
    // number of clock ticks used to generate the duty cyle of
    // the PWM signal.
    uint16_t ticks_red_on = (red_num * ticks_period)/255;
    uint16_t ticks_green_on = (green_num * ticks_period)/255;
    uint16_t ticks_blue_on = (blue_num * ticks_period)/255;

    // Initialze the IO pins used to control the
    // tri-color LED.
    ece353_MKII_RGB_IO_Init(true);

    // Complete the comments below that identify which
    // TimerA outputs will control the IO pins.
    //
    // Replace w and y with the correct TimerA number
    // Replace x and z with the correct CCR number.
    // RED      <--> TA0.3
    // GREEN    <--> TAw.x
    // BLUE     <--> TAy.z

    // ADD CODE BELOW
    //
    // Turn off the timer peripherals

    // Set the period for both TimerA peripherals.

    // Configure RED PWM duty cycle

    // Configure GREEN PWM duty cycle

    // Configure BLUE PWM duty cycle

    // Set the OUT MODE to be mode 7 for each
    // PWM output

    // Turn the first TimerA peripheral

    // Turn the second TimerA peripheral

}
