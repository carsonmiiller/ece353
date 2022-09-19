#include "msp.h"
#include "serial_debug.h"
/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    serial_debug_init();
    __enable_irq();
    serial_debug_put_string("\n\r\n\r");
    serial_debug_put_string("**************************************************\n\
r");
    serial_debug_put_string("ECE353 ICE 08 UART\n\r");
    serial_debug_put_string("**************************************************\n\
r");
    while(1)
    {
// check for when a new string has been received and print it to the
// terminal.
        if(newString){
            printf("Data Rxed: Hello ECE353\nData Rxed: %s", incoming);
            newString = FALSE;
            memset(incoming, 0, receivedCharCount);
            receivedCharCount = 0;
            break;
        }
    }
}
