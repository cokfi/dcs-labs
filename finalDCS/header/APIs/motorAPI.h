/*
 * motorAPI.h
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_APIS_MOTORAPI_H_
#define HEADER_APIS_MOTORAPI_H_

#include "../Timers/halTimers.h"
#include "../GPIO/halGPIO.h"

static int motorConfigured_flag;
static int start_pos_calibrated_flag;
static int angle_calibrated_flag;
static int motor_current_angle;
static int full_circle_steps;

void configureMotor();
int angleToSteps(float angle);
float stepsToAngle(steps);
int moveMotorBySteps(int steps, char direction);

float getNominalAngle();

void moveMotorByAngle(float dest_angle);

void calibrateMotorStartPosition();

int moveToStartPos();

int calibrateMotorAngle();

#endif /* HEADER_APIS_MOTORAPI_H_ */
