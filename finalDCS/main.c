//#include <msp430.h>
//#include "header/Timers/halTimers.h"
#include  <msp430g2553.h>          // MSP430x2xx

/**
 * main.c
 */
static unsigned int motorSequence = 0x10;

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL = 0;
    P1DIR = 0xF0;

    TACTL = 0;
    TACTL |= ID_3;
    TACCR0 = 82;

    TACTL |= MC_1 + TAIE;

    int i;
    for (i = 0; i < 30; i++)
    {

        if (motorSequence == 0x08)
        {
            motorSequence = 0x80;
        }
        else
        {
            motorSequence = motorSequence >> 1;
        }

        P1OUT = motorSequence;
        _BIS_SR(LPM0_bits);
    }
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    TACTL &= ~TAIFG;
    LPM0_EXIT;
}
