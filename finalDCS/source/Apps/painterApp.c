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
    __bic_SR_register(GIE);
    enableUartRxInterrupt();
    __bis_SR_register(CPUOFF + GIE);//  wait for ack
    if (getReceiveBuffer()!=ACKNOWLEDGE_MESSAGE)
        return;

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
        enableUartRxInterrupt();
        __bis_SR_register(CPUOFF + GIE);//  wait for ack
        int request = getReceiveBuffer();
        readJoysctickPos();
        if (request == 'x')
        {
            sendMessage(getVx());
        }
        else if (request == 'y')
        {
            sendMessage(getVy());
        }

    }
}

