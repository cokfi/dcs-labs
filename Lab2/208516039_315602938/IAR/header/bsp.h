#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430g2553.h>          // MSP430x2xx
// #include  <msp430xG46x.h>  // MSP430x4xx


#define   debounceVal      250
#define   LEDs_SHOW_RATE   0xFFFF  // 62_5ms

// LEDs abstraction
//#define LEDsArrPort        P1OUT
//#define LEDsArrPortDir     P1DIR
//#define LEDsArrPortSel     P1SEL

// Switches abstraction
//#define SWsArrPort         P2IN
//#define SWsArrPortDir      P2DIR
//#define SWsArrPortSel      P2SEL
//#define SWmask             0xF0

// PushButtons abstraction
#define PBsArrPort	   P1IN 
#define PBsArrIntPend	   P1IFG 
#define PBsArrIntEn	   P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL 
#define PBsArrPortDir      P1DIR 
#define PB0                0x01
#define PB1                0x02
#define PB2                0x04

#define LCD_C_SEL          P2SEL
#define LCD_D_SEL	        P1SEL
#define GeneratorDir       P2DIR
#define GeneratorSel       P2SEL

#define ADCArrPortSel     P1SEL
#define ADCArrPortDir     P1DIR

extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void ADCconfig(void);
#endif



