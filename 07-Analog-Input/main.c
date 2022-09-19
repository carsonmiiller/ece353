#include "msp.h"
#include "ece353.h"
#include "interrupts.h"

#define VOLT_0P85 ((int)(0.85/(3.3/4096))) // 1056      // 0.85 /(3.3/4096)
#define VOLT_2P50 ((int)(2.50/(3.3/4096))) // 3103      // 2.50 /(3.3/4096)

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    // Configure the IO pins that control the RGB LED on the MKII
    // DO NOT enable the primary function.
    ece353_MKII_RGB_IO_Init(false);

    // Configure the IO pins that control the RGB LED on the Launchpad
    ece353_rgb_init();

    // Configure just the X direction of the PS2 Joystick
    // as a single channel, single sample in the ADC14
    ece353_ADC14_PS2_XY();

    // Set up Timer32 to interrupt at a rate of 10Hz
    ece353_T32_1_Interrupt_Ms(100);

    // enable NVIC
    __enable_irq();

    // Wait forever
    while(1)
    {
        if(JOYSTICK_X_DIR > VOLT_2P50 )
        {
            ece353_rgb(true, false, false); // turn on red
        }
        else if(JOYSTICK_X_DIR < VOLT_0P85 )
        {
            ece353_rgb(false, true, false); // turn on green
        }
        else
        {
            ece353_rgb(false, false, true); // turn on blue
        }

        if(JOYSTICK_Y_DIR > VOLT_2P50 )
        {
            ece353_MKII_RGB_LED(true, false, false); // turn on red
        }
        else if(JOYSTICK_Y_DIR < VOLT_0P85 )
        {
            ece353_MKII_RGB_LED(false, true, false); // turn on green
        }
        else
        {
            ece353_MKII_RGB_LED(false, false, true); // turn on blue
        }
    }
}
