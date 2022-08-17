/*
 * motorApp.c
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#include "../../header/Apps/motorApp.h"

float xyToAngle(unsigned int x, unsigned int y)
{
    float angle = 0;

    //TODO complete
    return angle;
}

void motorControl()
{
    configureMotor();
    configureJoystick();
    configureUart();

    unsigned int x, y;
    int  joystick_angle;
    char messages_check;
    while (1)
    {
        messages_check = getReceiveBuffer();
        if (messages_check == EXIT_MESSAGE)
        {
            sendMessage(ACKNOWLEDGE_MESSAGE);
            return;
        }
        readJoysctickPos();
            x = getVx();
            y = getVy();
        if (x>500 & y>500) // first quarter
        {
            moveMotorByAngle(45);
        }
        else if (x<500 & y>500) // second
        {
            moveMotorByAngle(135);
        }

        else if(x<500 & y<500) // third
        {
            moveMotorByAngle(225);
        }
        else
        {
            moveMotorByAngle(315);
        }

        joystick_angle = xyToAngle(x, y);
        moveMotorByAngle(joystick_angle);

    }

}
