/*
 * halTimers.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#include  "../../header/Timers/halTimers.h"

#define DELAY_CONST 0x7D // 10^-3 * 10^6 / 8 (ms * MHz * ID , assuming 1MHz clock and input divider 8)

direction_right = 1;
motor_input = 0x01;
steps_counter = 0;
ablolute_pos = 0;
scan = 0;

static int motorTimerConfigured = 0;
static int delayTimerConfigured = 0;

void configureMotorTimer()
{
    TA0CTL = 0; // Make sure timer not working
    TA0CTL = TASSEL_2 + TACLR + TAIE;
    TA0CTL |= ID_3;

    TA0CCR0 = 0x9c4; // for 5-50 Hz this values should be between 0x9c4(50 Hz) and 0x61a8(5 Hz)
    TA0CCTL0 |= CCIE;
    motorTimerConfigured = 1;
}

void startMotorTimer()
{
    if (!motorTimerConfigured)
        configureMotorTimer();

    TA0CTL |= MC_1;
}

void stopMotorTimer()
{
    TA0CTL &= ~MC_3;
}

void configureDelayTimer()
{
    TA1CTL = 0; // Make sure timer not working
    TA1CTL = TASSEL_2 + TACLR + TAIE;
    TA1CTL |= ID_3;
    delayTimerConfigured = 1;
}

void startDelayTimer()
{
    if (!delayTimerConfigured)
        configureDelayTimer();
    TA1CTL |= MC_1;
}

//void setDelay(int delay)
//{
//    TA1CCR0 = delay;
//}

//void startScan()
//{
//    scan = 1;
//    startMotorTimer();
////    while (scan)
////    {
////        __bis_SR_register(CPUOFF + GIE);
//
//        /* The idea: Enable interrupts in the port connected to the joystick push-button.
//         * in the ISR for that button, reset the values of scan and stop the motorTimer.
//         *
//         * Note: not sure we really need the variable 'scan' and the while loop, it might work just with the ISR.
//         * we need to think about it  */
////    }
//}

void setSteps(int steps)
{
    steps_counter = steps;
}

void setStartingPoint()
{
    ablolute_pos = 0;
}

int getCurrentPos()
{
    return ablolute_pos;
}
void setDirection(char direction)
{
    if (direction == 'r')
        direction_right = 1;
    else
        direction_right = 0;
}

//-------------------------------------------------------------
//           interrupt vector Timer 0 (Motor Timer)
//-------------------------------------------------------------
#pragma vector=TIMER0_A0_VECTOR
__interrupt void motorTimerISR(void)
{

    if (direction_right)
    {
        P2OUT = (unsigned int) motor_input;
        if (motor_input == 1)
        {
            motor_input = 8;
            steps_counter--;
            ablolute_pos++;
        }
        else
        {
            motor_input = motor_input >> 1;
        }
    }
    if (!direction_right)
    {
        P2OUT = (unsigned int) motor_input;
        if (motor_input == 8)
        {
            motor_input = 1;
            steps_counter--;
            ablolute_pos--;
        }
        else
        {
            motor_input = motor_input << 1;
        }
    }
    TACTL &= ~TAIFG;
    __bic_SR_register_on_exit(CPUOFF+GIE); // Enable CPU so the main while loop continues
}

//-------------------------------------------------------------
//           interrupt vector Timer 1 (Delay Timer)
//-------------------------------------------------------------
#pragma vector=TIMER1_A0_VECTOR
__interrupt void delayTimerISR(void)
{
    TA0CTL &= ~MC_3; // Stop Timer
    TA0CTL &= ~TAIFG;
    __bic_SR_register_on_exit(CPUOFF+GIE); // Enable CPU so the main while loop continues
}
