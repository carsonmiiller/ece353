/*
 * opt3001.c
 *
 *  Created on: Mar 14, 2021
 *      Author: younghyunkim
 */

#include "opt3001.h"
#include "math.h"

/******************************************************************************
 * Initialize the opt3001 ambient light sensor on the MKII.  This function assumes
 * that the I2C interface has already been configured to operate at 100KHz.
 ******************************************************************************/

void opt3001_init(void)
{
    // reset value of CONFIG_REG = b1100.1000.0001.0000 = hc810

    // Initialize OPT3001

    // select primary function
    P4->SEL0 |= BIT6;
    P4->SEL1 &= ~BIT6;

    // set pin to be input
    P4->DIR &= ~BIT6;

    i2c_write_16(OPT3001_SLAVE_ADDRESS, CONFIG_REG, 0xc810);
}


/******************************************************************************
 * Returns the current ambient light in lux
 *  ******************************************************************************/
float opt3001_read_lux(void)
{
    // Read the Result register of OPT3001 and convert into Lux, then return.
    uint16_t result = i2c_read_16(OPT3001_SLAVE_ADDRESS, RESULT_REG);
    float exp = pow(2, (result >> 12));
    float frac = (result << 4) >> 4;
    float lux = 0.01 * exp * frac;
    return lux;

}

