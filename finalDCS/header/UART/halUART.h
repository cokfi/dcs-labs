/*
 * halUART.h
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_UART_HALUART_H_
#define HEADER_UART_HALUART_H_

#include  "bspUART.h"
#include  <msp430g2553.h>          // MSP430x2xx

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

static int sendUartNumber;
//static int switch0;
static int counter;
static int uartConfigured_flag;

static int messageRecieved_flag; //
static int messageSent_flag;

// TODO change vx vy to send/receive buffers
static unsigned int receive_buffer;
static unsigned int send_buffer;

void configureUart();
void enableUartRxInterrupt();
void setSendData(int msg);
void enableUartTxInterrupt();
int getReceiveBuffer();
int getMessageSentFlag();
int getMessageRecivedFlag();
int getUartConfiguredFlag();

//-------------------------------------------------------------
//           interrupt vector uartTx
//-------------------------------------------------------------
__interrupt void USCI0TX_ISR(void);

//-------------------------------------------------------------
//           interrupt vector uartRx
//-------------------------------------------------------------
__interrupt void USCI0RX_ISR(void);

#endif /* HEADER_UART_HALUART_H_ */
