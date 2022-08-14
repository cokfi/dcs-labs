/*
 * joystickAPI.c
 *
 *  Created on: 12 Aug 2022
 *      Author: rontal
 */
#include "../../header/APIs/joystickAPI.h"

read_available_flag = 0;
joystickEnable = 0;

void configureJoystick()
{
    configureADC();
    configurePushButton();
    enablePushButton();
}
void enableJoystick()
{
    joystickEnable=0;
}
void disableJoystick()
{
    joystickEnable=1;
}
void readJoysctickPos()
{
    read_available_flag= 0;
    while (!read_available_flag)
    {
        startADC();
        if (!checkXYvalid())
            __bis_SR_register(CPUOFF + GIE);
        read_available_flag = checkXYvalid();
    }
    disableADC();

    v_x = getVx();
    v_y = getVy();
    read_available_flag = 1;
}

int checkPushButton()
{
    return buttonPressed;
}
