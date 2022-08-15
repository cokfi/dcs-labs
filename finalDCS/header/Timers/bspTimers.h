/*
 * bspTimers.h
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_TIMERS_BSPTIMERS_H_
#define HEADER_TIMERS_BSPTIMERS_H_
#include  <msp430g2553.h>          // MSP430x2xx

typedef enum SourceSelect
{
    TACLK = TASSEL_0, ACLK = TASSEL_1, SMCLK = TASSEL_2, INCLK = TASSEL_2
} SourceSelect;

typedef enum ModeControl
{
    STOP = MC_0, UP = MC_1, CONT = MC_2, UPDOWN = MC_3
} ModeControl;

typedef enum InputDivider
{
    TIMER_DIV1 = ID_0, TIMER_DIV2 = ID_1, TIMER_DIV4 = ID_2, TIMER_DIV8 = ID_3
} InputDivider;

typedef enum CaptureMode
{
    NO_CAPTURE = CM_0, RISING = CM_1, FALLING = CM_2, BOTH = CM_3
} CaptureMode;

typedef enum OutMod
{
    SET = OUTMOD_0,
    TOGGLE_RESET = OUTMOD_1,
    SET_RESET = OUTMOD_2,
    TOGGLE = OUTMOD_3,
    RESET = OUTMOD_4,
    TOGGLE_SET = OUTMOD_5,
    RESET_SET = OUTMOD_6
} OutMod;

#endif /* HEADER_TIMERS_BSPTIMERS_H_ */
