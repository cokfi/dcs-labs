//#include <msp430.h>
//#include "header/Timers/halTimers.h"
#include  <msp430g2553.h>          // MSP430x2xx

/**
 * main.c
 */
static unsigned int motorSequence = 0x10;

static unsigned int v_x = 0x00;
static int v_y;
static int current_adc_channel = 0;
static int steps_counter = 0;
static int direction_right; // 1 - Spin Motor Right, 0 - Spin Motor Left
static int motor_input = 0x01;
static int ablolute_steps = 0;

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

void configureTimer()
{
    TA0CTL = 0; // Make sure timer not working
    TA0CTL = TASSEL_1 + TACLR + TAIE;

    TA0CCR0 = 0x485; // for 5-50 Hz this values should be between 0x285(50 Hz) and 0x199A(5 Hz)
}

void startTimer()
{
    TA0CTL |= MC_1;
}

void stopTimer()
{
    TA0CTL &= ~MC_3;
}

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Connect P2 to LEDs to see values
    P2SEL = 0;
    P2DIR = 0xFF;

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

#pragma vector=TA0IV_TAIFG
__interrupt void timer0ISR(void)
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
    __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues

}

