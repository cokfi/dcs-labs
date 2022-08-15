/*
 * halUART.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#include  "../../header/UART/halUART.h"
//#include  <msp430g2553.h>          // MSP430x2xx

#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

sendUartNumber = 0;
//static int switch0 = 0;
counter = 0;
uartConfigured_flag = 0;

messageRecieved_flag = 0; //
messageSent_flag = 0;
// TODO change vx vy to send/receive buffers
//receive_buffer;
//send_buffer;

void configureUart() // Moved to halUART
{
    if (CALBC1_1MHZ == 0xFF)                   // If calibration constant erased
    {
        while (1)
            ;                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                          // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2;                     // P1.1 = RXD, P1.2=TXD
    //P1DIR |= RXLED + TXLED;
    //P1OUT &= 0x00;

    UCA0CTL1 |= UCSSEL_2;                     // CLK = SMCLK
    UCA0BR0 = 104;                           //
    UCA0BR1 = 0x00;                           //
    UCA0MCTL = UCBRS0;               //
    UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
    uartConfigured_flag = 1;
}

void enableUartRxInterrupt()
{
    if (!uartConfigured_flag)
        configureUart();
    UCA0CTL1 &= ~UCSWRST;                   // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}

void enableUartTxInterrupt()
{
    if (!uartConfigured_flag)
        configureUart();
    IE2 |= UCA0TXIE;                          // Enable USCI_A0 RX interrupt
}
void setSendData(int msg)
{
    send_buffer = msg;
    messageSent_flag = 0;
}
int getReceiveBuffer()
{
    int var;
    var = receive_buffer;
    receive_buffer = 0;
    return var;
}
int getMessageSentFlag()
{
    if (messageSent_flag)
    {
        messageSent_flag =0;
        return 1;
    }
    return messageSent_flag;
}
int getMessageRecivedFlag()
{
    if (messageRecieved_flag)
        {
            messageRecieved_flag =0;
            return 1;
        }
    return messageRecieved_flag;

}
int getUartConfiguredFlag()
{
    return uartConfigured_flag;
}
//-------------------------------------------------------------
//           interrupt vector uartTx
//-------------------------------------------------------------
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{

    UCA0TXBUF = send_buffer;               // TX next sample, send LSB
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
    messageSent_flag = 1;
    //__bic_SR_register_on_exit(CPUOFF);
}

//-------------------------------------------------------------
//           interrupt vector uartRx
//-------------------------------------------------------------
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    receive_buffer = UCA0RXBUF;
    messageRecieved_flag = 1;
    __bic_SR_register_on_exit(CPUOFF);
}

