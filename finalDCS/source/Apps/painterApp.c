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

//        messages_check = checkMessages();
//        if (messages_check == EXIT_MESSAGE)
//        {
//            sendMessage(ACKNOWLEDGE_MESSAGE);
//            return;
//        }
        if (isButtonPressed())
        {
            sendMessage(BUTTON_PRESSED_MESSAGE);
        }

        readJoysctickPos();
        if (checkXYvalid())
        {
            x = v_x;
            y = v_y;
            sendMessage(x);
            sendMessage(y);
        }

    }
}

