/*
 * motorApp.h
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_APPS_MOTORAPP_H_
#define HEADER_APPS_MOTORAPP_H_

#include "../APIs/motorAPI.h"
#include "../APIs/joystickAPI.h"
#include "../APIs/communicationAPI.h"

float xyToAngle(int x, int y);
void motorControl();

#endif /* HEADER_APPS_MOTORAPP_H_ */
