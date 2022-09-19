#include "msp.h"
#include "i2c.h"
#include "opt3001.h"
#include "ece353.h"
#include <stdint.h>




void display_lux(float light)
{
    if(light < 200.0)
    {
        ece353_MKII_RGB_LED(false, false, true); // turn on BLUE
    }
    else if (light < 500.0)
    {
        ece353_MKII_RGB_LED(false, true, false); // turn on GREEN
    }
    else
    {
        ece353_MKII_RGB_LED(true, false, false); // turn on RED
    }
}
/**
 * main.c
 */
void main(void)
{
    float lux = 0.0;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    ece353_MKII_RGB_IO_Init(false);
    i2c_init();
    opt3001_init();

    while(1){
        lux = opt3001_read_lux();
        display_lux(lux);
    };



}

