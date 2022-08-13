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
    if (!uartConfigured_flag)
        configureUart();

    int message;
    if (messageRecieved_flag)
    {
        message = receive_buffer;
        messageRecieved_flag = 0;
        return message;
    }
    else
        return -1;
}

// check if message is available and wait if not
int readMessage()
{
    messageRecieved_flag = 0;
    if (!uartConfigured_flag)
        configureUart();

    enableUartRxInterrupt();
    __bis_SR_register(CPUOFF + GIE);
    return receive_buffer;
}

int sendMessage(unsigned int message_data)
{
    messageSent_flag = 0;
    if (!uartConfigured_flag)
        configureUart();
    setSendData(message_data);
    enableUartTxInterrupt();
    __bis_SR_register(CPUOFF + GIE); // Maybe take this out and use getters to access send/receive info
    setSendData(END_OF_LINE);
    enableUartTxInterrupt();
    __bis_SR_register(CPUOFF + GIE); // Maybe take this out and use getters to access send/receive info
//    if (messageSent_flag)
//        return 0;
    return 0;
}
