/*
 * halGPIO.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */
#include  "../../header/GPIO/halGPIO.h"

pushButtonConfigured = 0;
buttonPressed = 0;

void configurePushButton()
{
    P1SEL &= ~BIT5;
    P1DIR &= ~BIT5;
//    P1IE |= BIT5;
    pushButtonConfigured = 1;
}

int isButtonPressed()
{
    return buttonPressed;
}
void enablePushButton()
{
    if (!pushButtonConfigured)
        configurePushButton();
    P1IE |= BIT5;
}

void configureMotorPorts()
{
    // TODO - Complete
}

void configureJoystickPorts()
{
    // TODO - Complete
}
void blinkRGB(int x)
{
    return;
}

void rlcLEDs(int x)
{
    int ledsVal;
    int i;
    for (i; i < x; i++)
    {
        ledsVal = P2OUT >> 1;
        P2OUT = (unsigned int) ledsVal;
        delay();
    }
}

void rrcLEDs(int x)
{
    int ledsVal;
    int i;
    for (i; i < x; i++)
    {
        ledsVal = P2OUT << 1;
        P2OUT = (unsigned int) ledsVal;
        delay();
    }
}

void setDelay(int d)
{
    TA1CCR0 = d << 7; // SHL(d,7) = d*2^7 = d*128 ~ d*125 = 0x7D (see explanation in define)
}

void clearAllLEDs()
{
    P2OUT = (unsigned int) 0;
}

void stepperDeg(int p)
{
    return;
}

void sleep()
{
    __bic_SR_register(CPUOFF + GIE);
}

void executeCommand(int command)
{
    int opcode, operand, operandL, operandR;

    if (command >> 16 != 0)
    {
        opcode = 7;
        operandL = (command & 0x00FF00) >> 8;
        operandR = command & 0x0000FF;
    }
    else
    {
        opcode = command >> 8; // Opcode is in 8 leftmost bits
        operand = command && 0x0F; // Operand is in 8 rightmost bits
    }

    switch (opcode)
    {
    case 1:
        blinkRGB(operand);
        break;
    case 2:
        rlcLEDs(operand);
        break;
    case 3:
        rrcLEDs(operand);
        break;
    case 4:
        setDelay(operand);
        break;
    case 5:
        clearAllLEDs();
        break;
    case 6:
        stepperDeg(operand);
        break;
    case 7:
        stepperScan(operandL, operandR);
        break;
    case 8:
        sleep();
        break;
    default:
        break;
    }
}

//-------------------------------------------------------------
//           interrupt vector uartRx
//-------------------------------------------------------------
#pragma vector = PORT1_VECTOR
__interrupt void port1ISR(void)
{
    int i;
    for (i=0; i<debounceVal; i++)
    {
        //delay 250 clk
    }      
    P1IFG &= ~BIT5;
    buttonPressed = 1;
    __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues

}
