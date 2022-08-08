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

void configureADC()
{
    ADC10CTL0 = 0;
    ADC10CTL0 |= ADC10ON + MSC+ADC10SHT_2; // Turn Module On
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

int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Connect P2 to LEDs to see values
    P2SEL = 0;
    P2DIR = 0xFF;

    configureADC();
    startADC();
    int v_x_disp, v_y_disp;
    while (1)
    {
        //ADC10CTL0 &= ~ADC10IE;
        P2OUT = (unsigned int)ADC10MEM>>8;
        //ADC10CTL0 |= ADC10IE;
        //__bis_SR_register(CPUOFF + GIE);
        //v_x_disp = v_x & 0x0F; // Keep right 4 bits
        //v_y_disp = v_y << 4 & 0xF0; // Keep left 4 bits

    }
    return 0;
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{

    ADC10CTL0 &= ~ADC10IFG;
    if (current_adc_channel == 0)
    {
        v_x = (unsigned int)ADC10MEM;
    }
    else
    {
        //v_y = ADC10MEM;
    }
    current_adc_channel ^= current_adc_channel;
    __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues
}