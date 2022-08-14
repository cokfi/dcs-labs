/*
 * halADC.h
 *
 *  Created on: 3 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_ADC_HALADC_H_
#define HEADER_ADC_HALADC_H_

#include  "bspADC.h"

static int adcChannel;
static int v_x;
static int v_y;
static int xy_valid;
static int current_adc_channel;
static int adcConfigured;

void configureADC();

void disableADC();

void startADC();

int getVx();

int getVy();

int checkXYvalid();

//-------------------------------------------------------------
//           interrupt vector ADC10
//-------------------------------------------------------------
__interrupt void ADC10_ISR(void);

#endif /* HEADER_ADC_HALADC_H_ */
