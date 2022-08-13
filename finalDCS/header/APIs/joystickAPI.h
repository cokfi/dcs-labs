/*
 * joystickAPI.h
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_APIS_JOYSTICKAPI_H_
#define HEADER_APIS_JOYSTICKAPI_H_
#include "../ADC/halADC.h"
#include "../GPIO/halGPIO.h"

#define UP_THRESHOLD 0
#define DOWN_THRESHOLD 0

static int v_x;
static int v_y;
static int read_available_flag;

void configureJoystick();

void readJoysctickPos();

int checkPushButton();
#endif /* HEADER_APIS_JOYSTICKAPI_H_ */
