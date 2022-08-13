/*
 * halGPIO.h
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_GPIO_HALGPIO_H_
#define HEADER_GPIO_HALGPIO_H_

#include  <msp430g2553.h>          // MSP430x2xx

static int pushButtonConfigured;
static int buttonPressed;

void configurePushButton();

void enablePushButton();

void configureMotorPorts();

void configureJoystickPorts();
void blinkRGB(int x);

void rlcLEDs(int x);

void rrcLEDs(int x);

void setDelay(int d);
void clearAllLEDs();

void stepperDeg(int p);

void sleep();

void executeCommand(int command);
//-------------------------------------------------------------
//           interrupt vector uartRx
//-------------------------------------------------------------
__interrupt void port1ISR(void);

#endif /* HEADER_GPIO_HALGPIO_H_ */
