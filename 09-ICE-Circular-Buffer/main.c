#include "msp.h"
#include "circular_buffer.h"

/**
 * main.c
 */
void main(void)
{
    Circular_Buffer *Rx_Buffer;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    if(circular_buffer_test_0(40))
    {
        while(1){};
    }
    else
    {
        while(1)
        {

        }
    }
}
