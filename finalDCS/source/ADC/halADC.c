/*
 * halADC.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */
#include  "../../header/ADC/halADC.h"
//
//static int adcChannel = 0;
//static int v_x = 0x00;
//static int v_y = 0x00;
//static int xy_valid = 0;
//static int current_adc_channel = 0;
//static int adcConfigured = 0;

adcChannel = 0;
//v_x = 0;
//v_y = 0;
xy_valid = 0;
adcConfigured = 0;

void configureADC()
{
    ADC10CTL0 = 0;
    ADC10CTL0 |= ADC10ON+ ADC10SHT_1; // Turn Module On
    ADC10CTL1 |= CONSEQ_0; // Repeat Sequence of Channels Mode
    ADC10CTL1 |= SHS_0; // SH
    ADC10CTL1 |= INCH_4; // Highest Channel in the sequence is A4
    ADC10AE0  |= BIT0 + BIT3;
    adcConfigured = 1;
}
void chooseADCchannel(int chosenChannel)
{
    if (chosenChannel ==1){
        ADC10CTL1 &= ~INCH_15;//clear
        ADC10CTL1 |= INCH_3; // Highest Channel in the sequence is A3
    }
    else if (chosenChannel ==0)
    {
         ADC10CTL1 &= ~INCH_15;
         ADC10CTL1 |= INCH_4; // Highest Channel in the sequence is A4
    }
}
void disableADC()
{
    ADC10CTL0 &= ~ENC;
    ADC10CTL0 &= ~ADC10ON;
    ADC10CTL0 &= ~ADC10IE;
    ADC10CTL0 &= ~ADC10SC;
}
//void killADC()
//{
//    ADC10CTL0 = 0x0;
//    ADC10CTL1 = 0x0;
//    adcConfigured = 0;
//}


void startADC()
{

    xy_valid = 0;
    if (!adcConfigured)
        configureADC();
    ADC10CTL0 |= ADC10ON;
    ADC10CTL1 |= CONSEQ_0; // Repeat Sequence of Channels Mode
    ADC10CTL0 |= ADC10IE;
    ADC10CTL0 |= ENC; // Enable Conversions (Must be reset before changing configuration)
    ADC10CTL0 |= ADC10SC; // Start Conversion
    __bis_SR_register(CPUOFF + GIE);
    chooseADCchannel(adcChannel);
    ADC10CTL0 |= ADC10ON;
    ADC10CTL1 |= CONSEQ_0; // Repeat Sequence of Channels Mode
    ADC10CTL0 |= ADC10IE;
    ADC10CTL0 |= ENC; // Enable Conversions (Must be reset before changing configuration)
    ADC10CTL0 |= ADC10SC; // Start Conversion
    __bis_SR_register(CPUOFF + GIE);
    chooseADCchannel(adcChannel);
}

unsigned int getVx()
{
    return v_x;
}

unsigned int getVy()
{
    return v_y;
}

int checkXYvalid()
{
    return xy_valid;
}
//-------------------------------------------------------------
//           interrupt vector ADC10
//-------------------------------------------------------------
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    if (adcChannel == 0)
    {
        v_y = ADC10MEM;
        adcChannel = 1;
    }
    else
    {
        v_x = ADC10MEM;
        xy_valid = 1;
        adcChannel = 0;
    }
    ADC10CTL0 &= ~ENC;
    __bic_SR_register_on_exit(CPUOFF); // Enable CPU so the main while loop continues
}
