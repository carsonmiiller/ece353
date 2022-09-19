#include "msp.h"
#include "serialDebug.h"

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    serial_debug_init();

    __enable_irq();

    printf("\n\r\n\r");
    printf("**************************************************\n\r");
    printf("ECE353 ICE 10 UART Circular Buffers\n\r");
    printf("**************************************************\n\r");
    while(1)
    {
        // check for when a new string has been received and print it to the
        // terminal.
        if(ALERT_STRING)
        {
            ALERT_STRING = false;
            printf("Data Rxed : ");
            printf(Rx_String);
            printf("\r\n");
            Rx_Char_Count = 0;
            memset(Rx_String,0,80);
        }
    }
}
