/*
 * bspADC.c
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal (aka tajoro)
 */

#include  "../../header/ADC/bspADC.h"



void adcReset(){
    ADC10CTL0 = 0x00; 
    ADC10CTL1 = 0x00;

}

void adcSetInputChannel(InputChannel ic){
ADC10CTL1 = ic;                       // input A1-A3
}



