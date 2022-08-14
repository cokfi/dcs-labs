/*
 * communicationAPI.c
 *
 *  Created on: 12 Aug 2022
 *      Author: rontal
 */

#include "../../header/APIs/communicationAPI.h"

// check if message is available but don't wait if not
int checkMessages()
{
    if (!getUartConfiguredFlag())
        configureUart();

    int message;
    if (getMessageRecivedFlag())
    {
        message = getReceiveBuffer();
        return message;
    }
    else
        return -1;
}

// check if message is available and wait if not
int readMessage()
{
    if (!getUartConfiguredFlag())
        configureUart();

    enableUartRxInterrupt();
    if (!getMessageRecivedFlag())
    {
        __bis_SR_register(CPUOFF + GIE);
    }

    return getReceiveBuffer();
}

int sendMessage(unsigned int message_data)
{
    if (!getUartConfiguredFlag())
        configureUart();
    setSendData(message_data);
    enableUartTxInterrupt();
    if (!getMessageSentFlag())
    {
        __bis_SR_register(CPUOFF + GIE); // Maybe take this out and use getters to access send/receive info
    }
    return 0;
}
