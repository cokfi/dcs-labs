/*
 * halTimers.h
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_TIMERS_HALTIMERS_H_
#define HEADER_TIMERS_HALTIMERS_H_

#include  "bspTimers.h"

#define DELAY_CONST 0x7D // 10^-3 * 10^6 / 8 (ms * MHz * ID , assuming 1MHz clock and input divider 8)

static int direction_right;
static int motor_input;
static int steps_counter;
static int ablolute_pos;
static int scan;

static int motorTimerConfigured;
static int delayTimerConfigured;

void configureMotorTimer();

void startMotorTimer();

void stopMotorTimer();
void configureDelayTimer();

void startDelayTimer();

void setSteps(int steps);
void setStartingPoint();

int getCurrentPos();
void setDirection(char direction);

//-------------------------------------------------------------
//           interrupt vector Timer 0 (Motor Timer)
//-------------------------------------------------------------
__interrupt void motorTimerISR(void);

//-------------------------------------------------------------
//           interrupt vector Timer 1 (Delay Timer)
//-------------------------------------------------------------

__interrupt void delayTimerISR(void);

#endif /* HEADER_TIMERS_HALTIMERS_H_ */
