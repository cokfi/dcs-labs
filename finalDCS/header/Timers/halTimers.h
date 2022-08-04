/*
 * halTimers.h
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_TIMERS_HALTIMERS_H_
#define HEADER_TIMERS_HALTIMERS_H_

#include  "bspTimers.h"

typedef enum SourceSelect{
    ACLK,SMCLK
} SourceSelect;

typedef enum ModeControl{
    STOP,UP,CONT,UPDOWN
} ModeControl;

typedef enum InputDivider{
    TIMER_ID1,TIMER_ID2,TIMER_ID4,TIMER_ID8
}InputDivider;

typedef enum CaptureMode{
    NO_CAPTURE,RISING,FALLING,BOTH
}CaptureMode;


#endif /* HEADER_TIMERS_HALTIMERS_H_ */
