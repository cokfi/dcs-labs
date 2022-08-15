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
    int messages_check, joystick_angle;
    while (1)
    {
        messages_check = checkMessages();
        if (messages_check == EXIT_MESSAGE)
        {
            sendMessage(ACKNOWLEDGE_MESSAGE);
            return;
        }
        readJoysctickPos();
        if (read_available_flag)
        {
            x = v_x;
            y = v_y;
        }

        joystick_angle = xyToAngle(x, y);
        moveMotorByAngle(joystick_angle);

    }

}
