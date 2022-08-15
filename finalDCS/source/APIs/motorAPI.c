/*
 * motorAPI.c
 *
 *  Created on: 12 Aug 2022
 *      Author: rontal
 */

#include "../../header/APIs/motorAPI.h"
motorConfigured_flag = 0;
start_pos_calibrated_flag = 0;
angle_calibrated_flag = 0;
//nominal_angle;
//motor_current_angle;
//full_circle_steps;

void configureMotor()
{
    configureMotorPorts();
    configureMotorTimer();
    configurePushButton();
    motorConfigured_flag = 1;
}

int angleToSteps(float angle)
{
    return (int) (angle / nominal_angle);
}

float stepsToAngle( steps)
{
    return (float) steps * nominal_angle;
}

int moveMotorBySteps(int steps, char direction)
{
    if (!motorConfigured_flag)
        configureMotor();

    int previous_pos = getCurrentPos();
    setSteps(steps);
    setDirection(direction);
    startMotorTimer();
    while (steps_counter != 0)
    {
        __bis_SR_register(CPUOFF + GIE);
    }
    stopMotorTimer();

    int current_pos = getCurrentPos();

    if (current_pos > full_circle_steps)
        current_pos = current_pos - full_circle_steps;
    if (current_pos < -full_circle_steps)
        current_pos = current_pos + full_circle_steps;

    motor_current_angle = stepsToAngle(current_pos);

    if (current_pos - previous_pos == steps)
        return 0;
    else if (previous_pos - current_pos == steps)
        return 0;
    else
        return -1;
}

void moveMotorByAngle(float dest_angle)
{
    int direction;
    int dphi = dest_angle - motor_current_angle;
    if (dphi > 0)
        direction = 1;
    else
        direction = 0;

    int steps = angleToSteps(dphi);
    moveMotorBySteps(steps, direction);
}

void calibrateMotorStartPosition()
{
    if (!motorConfigured_flag)
        configureMotor();
    enablePushButton();
    __bis_SR_register(CPUOFF + GIE);
    if (buttonPressed)
        buttonPressed = 0;
    startMotorTimer();
    while (!buttonPressed)
    {
        __bis_SR_register(CPUOFF + GIE);
    }
    stopMotorTimer();
    setStartingPoint();
    start_pos_calibrated_flag = 1;
}

int moveToStartPos()
{
    if (!start_pos_calibrated_flag)
        return -1;

    int direction, steps;
    int current_pos = getCurrentPos();
    if (current_pos > 0)
    {
        direction = 'l';
        steps = current_pos;
    }
    else
    {
        direction = 'r';
        steps = -current_pos;
    }
    int status = moveMotorBySteps(steps, direction);

    return status;
}

int calibrateMotorAngle()
{
    if (!start_pos_calibrated_flag)
        calibrateMotorStartPosition();

    int status = moveToStartPos();

    if (status != 0)
        return 1;

    enablePushButton();
    __bis_SR_register(CPUOFF + GIE);
    if (buttonPressed)
        buttonPressed = 0;

    startMotorTimer();
    while (!buttonPressed)
    {
        __bis_SR_register(CPUOFF + GIE);
    }
    stopMotorTimer();
    full_circle_steps = getCurrentPos();

    nominal_angle = (float) full_circle_steps / 360;

    angle_calibrated_flag = 1;

    return 0;
}

