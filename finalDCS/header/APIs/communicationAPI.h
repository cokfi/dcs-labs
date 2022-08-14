/*
 * communicationAPI.h
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_APIS_COMMUNICATIONAPI_H_
#define HEADER_APIS_COMMUNICATIONAPI_H_

#include "../UART/halUART.h"

#define EXIT_MESSAGE 'b'
#define ERROR_MESSAGE 'e'
#define ACKNOWLEDGE_MESSAGE 'a'
#define BUTTON_PRESSED_MESSAGE 'p'
#define NO_COMMAND_MESSAGE 'n'
#define UP_MESSAGE 'u'
#define DOWN_MESSAGE 'd'
#define END_OF_LINE '\n'
// check if message is available but don't wait if not
int checkMessages();

// check if message is available and wait if not
int readMessage();

int sendMessage(unsigned int message_data);

#endif /* HEADER_APIS_COMMUNICATIONAPI_H_ */