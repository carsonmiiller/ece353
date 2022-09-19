/*
 * accelerometer.h
 *
 *  Created on: May 3, 2022
 *      Author: cmiller77
 */

#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#define X_AXIS_PORT     P6
#define Y_AXIS_PORT     P4
#define Z_AXIS_PORT     P4
#define X_AXIS_PIN      BIT1
#define Y_AXIS_PIN      BIT0
#define Z_AXIS_PIN      BIT2

void accel_init(void);

#endif /* ACCELEROMETER_H_ */
