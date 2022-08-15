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
    __bis_SR_register(GIE);

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
            __bis_SR_register(GIE);
        }
        else
        {
            sendMessage(NO_COMMAND_MESSAGE);
            __bis_SR_register(GIE);
        }

        enableUartRxInterrupt();

        int request = getReceiveBuffer();
//        if (request == 0)
//            __bis_SR_register(CPUOFF + GIE);// wait for request
        readJoysctickPos();
        if (request == 'x')
        {
            sendMessage((getVx()+2048)>>2);
            __bis_SR_register(GIE);
        }
        else if (request == 'y')
        {
            sendMessage((getVy()+2112)>>2);
            __bis_SR_register(GIE);
        }

        enableUartRxInterrupt();
        request = getReceiveBuffer();
//        if (request == 0)
//            __bis_SR_register(CPUOFF + GIE);// wait for request
       if (request == 'x')
       {
           sendMessage((getVx()+2048)>>2);
           __bis_SR_register(GIE);
       }
       else if (request == 'y')
       {
           sendMessage((getVy()+2112)>>2);
           __bis_SR_register(GIE);
       }

    }
}

