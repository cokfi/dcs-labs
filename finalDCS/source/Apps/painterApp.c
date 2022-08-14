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
        else
        {
            sendMessage(NO_COMMAND_MESSAGE);
        }

        enableUartRxInterrupt();
        __bis_SR_register(CPUOFF + GIE);// debug RX
        int request = getReceiveBuffer();
        readJoysctickPos();
        if (request == 'x')
        {
            sendMessage((getVx()+2048)>>2);
        }
        else if (request == 'y')
        {
            sendMessage((getVy()+2112)>>2);
        }

        enableUartRxInterrupt();
       __bis_SR_register(CPUOFF + GIE);// debug RX
       request = getReceiveBuffer();
       if (request == 'x')
       {
           sendMessage((getVx()+2048)>>2);
       }
       else if (request == 'y')
       {
           sendMessage((getVy()+2112)>>2);
       }

    }
}

