/*
 * bspTimers.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */
#include  "../../header/Timers/bspTimers.h"

//  *** Structure ***
//  Registers
//      Fields
//

// TACTL
void timerResetCounter()
{
    TACTL |= TACLR;
    return;
}

void timerStart()
{
    return;
}

void timerStop()
{
    TACTL &= ~MC_3;
    return;
}

void timerSetModeControl(const ModeControl mc)
{
    TACTL &= ~MC_0;
    TACTL |= mc;
}

void timerSetSourceSelect(const SourceSelect ssel)
{
    TACTL &= ~ssel;
    TACTL |= ssel;
}

void timerSetInputDivider(const InputDivider id)
{
    TACTL &= ~ ID_0;
    TACTL |= id;
}

void timerEnableInterrupt(void)
{
    TACTL |= TAIE;
}

void timerDisableInterrupt(void)
{
    TACTL &= ~TAIE;
}

void timerClearInterruptFlag(void)
{
    TACTL &= ~TAIFG;
}

void timerSetCounter(const int counter)
{
    TAR = counter;
}

int timerGetCounter(void)
{
    return TAR;
}

// Capture & Compare
void timerSetUpperBound(const int upper_bound)
{
    TA0CCR0 = upper_bound;
}

int timerGetUpperBound(void)
{
    return TA0CCR0;
}

void timerSetCaptureMode(const CaptureMode cm)
{
    TACCTL0 |= CAP;
    TACCTL0 &= ~CM_3;
    TACCTL0 |= cm;
}

void timerSetOutMod(const OutMod om)
{
    TACCTL0 &= ~RESET_SET;
    TACCTL0 |= om;
}

