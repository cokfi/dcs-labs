#ifndef _bsp_H_
#define _bsp_H_

//#include  <msp430g2553.h>          // MSP430x2xx
#include  <msp430xG46x.h>  // MSP430x4xx

/*
  Ports and Connections:

  1. PB0-PB2        => P1.0-P1.2 
  2. LCD D4-D7      => P1.4-P1.7
  3. LCD Ctl Lines  => P2.5-P2.7
  4. Buzzer         => P2.2
  5. Keypad         => P10
  6. Keypad Int     => P2.1
*/

#define   debounceVal      250
#define   LEDs_SHOW_RATE   0xFFFF  // 62_5ms

// LEDs abstraction
#define LEDsArrPort        P1OUT
#define LEDsArrPortDir     P1DIR
#define LEDsArrPortSel     P1SEL

// Switches abstraction
#define SWsArrPort         P2IN
#define SWsArrPortDir      P2DIR
#define SWsArrPortSel      P2SEL
#define SWmask             0x0F

// PushButtons abstraction
#define PBsArrPort	       P1IN 
#define PBsArrIntPend	   P1IFG
#define PBsArrIntEn	       P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL 
#define PBsArrPortDir      P1DIR 
#define PB0                0x10
#define PB1                0x20
#define PB2                0x40
#define PB3                0x80

// Keypad abstraction
//    Keypad Interrupt
#define KeypadIntPort     P2IN
#define KeypadIntPend	    P2IFG 
#define KeypadIntEn	      P2IE
#define KeypadIntEdgeSel  P2IES
#define KeypadIntSel      P2SEL 
#define KeypadIntDir      P2DIR
#define IRQ               0x01

#define KeypadArrPort   P10IN
#define KeypadArr       P10IN

// Buzzer Abstraction
#define BuzzerArrPort   P2OUT
#define BuzzerSel       P2SEL
#define BuzzerDir       P2DIR

#define Buzzer          0x02



extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void DMAConfig(void);
extern void enableTransfersDMA(void);
extern void KeypadConfig(void);
extern void startDMATransfers(void);
//extern void recordConfig(void);
#endif



