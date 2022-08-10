//#include <msp430.h>
//#include "header/Timers/halTimers.h"
#include  <msp430g2553.h>          // MSP430x2xx

/**
 * main.c
 */
#define DELAY_CONST 0x7D // 10^-3 * 10^6 / 8 (ms * MHz * ID , assuming 1MHz clock and input divider 8)

static unsigned int motorSequence = 0x10;

static unsigned int v_x = 0x00;
static int v_y;
static int current_adc_channel = 0;
static int steps_counter = 0;
static int direction_right; // 1 - Spin Motor Right, 0 - Spin Motor Left
static int motor_input = 0x01;
static int ablolute_steps = 0;
static int scan;

void delay()
{
    startDelayTimer();
    __bic_SR_register(CPUOFF + GIE);
}

void configureLEDs()
{
    // Connect P2 to LEDs to see values
    P2SEL = 0;
    P2DIR = 0xFF;
}

void setLEDs(unsigned int val)
{
    P2OUT |= val;
}

void resetLEDs(unsigned int val)
{
    P2OUT &= ~val;
}

void configureADC()
{
    ADC10CTL0 = 0;
    ADC10CTL0 |= ADC10ON + MSC + ADC10SHT_2; // Turn Module On
    ADC10CTL1 |= CONSEQ_3; // Repeat Sequence of Channels Mode
    ADC10CTL1 |= SHS_0; // SH
    ADC10CTL1 |= INCH_1; // Highest Channel in the sequence is A1
    ADC10CTL1 |= ADC10DF + ADC10DIV_4; // 2's Complement format
//ADC10CTL1 &= ~ADC10DF;// Binary format
}

void startADC()
{
    //ADC10CTL0 |= ADC10IE;
    ADC10CTL0 |= ENC; // Enable Conversions (Must be reset before changing configuration)
    ADC10CTL0 |= ADC10SC; // Start Conversion
}

void configureMotorTimer()
{
    TA0CTL = 0; // Make sure timer not working
    TA0CTL = TASSEL_2 + TACLR + TAIE;
    TA0CTL |= ID_3;

    TA0CCR0 = 0x61a8; // for 5-50 Hz this values should be between 0x285(50 Hz) and 0x199A(5 Hz)
    TA0CCTL0 |= CCIE;
}

void startMotorTimer()
{
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
}

void startDelayTimer()
{
    TA0CTL |= MC_1;
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

void stepperScan(int left, int right)
{
    scan = 1;
    startMotorTimer();
    while (scan)
    {
        __bis_SR_register(CPUOFF + GIE);

        /* The idea: Enable interrupts in the port connected to the joystick push-button.
         * in the ISR for that button, reset the values of scan and stop the motorTimer.
         *
         * Note: not sure we really need the variable 'scan' and the while loop, it might work just with the ISR.
         * we need to think about it  */
    }
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

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    configureLEDs();
    configureADC();
    configureTimer();
    startADC();
    int steps_to_make = 10;
    direction_right = 1;
    startTimer();
    while (1)
    {
//        P2OUT = (unsigned int)ADC10MEM>>8;

        if (steps_counter > steps_to_make)
        {
            stopTimer();
        }
        __bis_SR_register(CPUOFF + GIE);
    }
    return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void motorTimerISR(void)
{
    if (direction_right)
    {
        P2OUT = (unsigned int) motor_input;
        if (motor_input == 1)
        {
            motor_input = 8;
            steps_counter++;
            ablolute_steps++;
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
            steps_counter++;
            ablolute_steps--;
        }
        else
        {
            motor_input = motor_input << 1;
        }
    }
    TACTL &= ~TAIFG;
    __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues

}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void delayTimerISR(void)
{
    TA0CTL &= ~MC_3; // Stop Timer
    TA0CTL &= ~TAIFG;
    __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues
}
