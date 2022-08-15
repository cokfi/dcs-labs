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

#define UP_THRESHOLD 700
#define DOWN_THRESHOLD 300

static int v_x;
static int v_y;
static int read_available_flag;
static int joystickEnable;

void configureJoystick();

void readJoysctickPos();
void enableJoystick();
void disableJoystick();

int checkPushButton();
#endif /* HEADER_APIS_JOYSTICKAPI_H_ */
