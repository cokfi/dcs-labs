/*
 * painterApp.c
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#include "../../header/Apps/painterApp.h"
void painter()
{
    configureJoystick();
    configureUart();

    int x, y, messages_check;
    while (1)
    {

        if (isButtonPressed())
        {
            sendMessage(BUTTON_PRESSED_MESSAGE);
        }

        char request = getReceiveBuffer();

        readJoysctickPos();
        if (request == 'x')
        {
            sendMessage((getVx())>>2);
        }
        request = getReceiveBuffer();

       if (request == 'y')
       {
           sendMessage((getVy())>>2);
       }
    }
}

