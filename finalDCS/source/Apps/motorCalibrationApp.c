/*
 * motorCalibrationApp.c
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#include "../../header/Apps/motorCalibrationApp.h"

void motorCalibration()
{
    configureMotor();
    configureJoystick();
    configureUart();

    while (!(start_pos_calibrated_flag && angle_calibrated_flag))
    {
        calibrateMotorStartPosition();
        sendMessage('c');
        calibrateMotorAngle();
    }
    sendMessage(full_circle_steps);
    sendMessage(nominal_angle);
    sendMessage(EXIT_MESSAGE);
    return;
}

