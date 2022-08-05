/*
 * halTimers.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#include  "../../header/Timers/halTimers.h"

//static int timerIntCounter;
//
static unsigned int motorSequence = 0x10;
//
//void timerConfigForMotor()
//{
//    TACTL = 0;  // Reset Timer
//    TACTL |= UP;
//}
//
//void setCounter(int val)
//{
//    timerIntCounter = val;
//}
//
//int getCount()
//{
//    return timerIntCounter;
//}

void test(int steps)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1SEL = 0;
    P1DIR = 0xF0;

    TACTL = 0;
    TACTL |= ID_3;
    TACCR0 = 82;

    TACTL |= MC_1 + TAIE;

    int i;
    for (i = 0; i < steps; i++)
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

}
//void setFreq(int hz)
//{
//
//}
//
//void setPeriod(int ms)
//{
//
//}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
    TACTL &= ~TAIFG;
    LPM0_EXIT;
}
