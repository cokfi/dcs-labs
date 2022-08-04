/*
 * halTimers.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#include  "../../header/Timers/halTimers.h"


//  *** Structure ***
//  Registers
//      Fields
volatile unsigned int * CTL = &TA0CTL;  // ConTroL register - for configuration

    int const CLR = TACLR;  // CLeaR bit
    int const IE = TAIE;    // Interrupt Enable
    int const  IFG = TAIFG;  // Interrupt Flag
    volatile unsigned int * R = &TA0R;   // counteR - count of Timer_A

volatile unsigned int * CCTL = &TACCTL0;  // Capture Compare Control register - for configuration






void timerResetCounter()
{
    return;
}

void timerStart()
{
    return;
}

void timerStop()
{
    return;
}

void timerSetSourceSelect(const SourceSelect ssel)
{
    *CTL |= ssel;
}

void timerSetInputDivider(const InputDivider id)  {
    *CTL |= id;
}

void timerSetModeControl(const ModeControl mc)  {
    *CTL |= mc;
}

void timerEnableInterrupt(void)  {
    *CTL |= IE;
}

void timerDisableInterrupt(void)  {
    *CTL &= ~IE;
}

void timerClearInterruptFlag(void)  {
    *CTL &= ~IFG;
}

void timerSetCounter(const int counter) {

}

int timerGetCounter(void) {
    return *R;
}

void timerSetUpperBound(const int upper_bound) {

}

int timerGetUpperBound(void) {
    return 0;
}

void timerIncreaseCounter(void) {

}

void timerSetCaptureMode(const CaptureMode cm)
{

}





#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{

    timerClearInterruptFlag();
}
