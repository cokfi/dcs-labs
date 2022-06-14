#ifndef _bsp_H_
#define _bsp_H_
#include  <msp430g2553.h>          // MSP430x2xx
#include  "../header/app.h"    		// private library - APP layer
/*
  Ports and Connections:


  Potentiometer     => P1.3
  2. LCD D4-D7      => P1.4-P1.7
  RGB L.E.Ds        => P2.0-P2.2 
  3. LCD Ctl Lines  => P2.5-P2.7 

  not connected but in use:
  uart Rx at pin P1.1
  uart Tx at pin P1.2
  
*/
#define TXLED BIT0
#define RXLED BIT6
#define TXD BIT2
#define RXD BIT1

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
#define PBsArrPort	   P1IN 
#define PBsArrIntPend	   P1IFG
#define PBsArrIntEn	   P1IE
#define PBsArrIntEdgeSel   P1IES
#define PBsArrPortSel      P1SEL 
#define PBsArrPortDir      P1DIR 
#define PB0                0x01
#define PB1                0x02
#define PB2                0x04
#define PB4                0x08


// Keypad abstraction
//    Keypad Interrupt
#define KeypadIntPort     P2IN
#define KeypadIntPend	  P2IFG 
#define KeypadIntEn	  P2IE
#define KeypadIntEdgeSel  P2IES
#define KeypadIntSel      P2SEL 
#define KeypadIntDir      P2DIR
#define IRQ               0x02

#define KeypadIn        P10IN
#define KeypadOut       P10OUT
#define KeypadSel       P10SEL
#define KeypadDir       P10DIR



// Buzzer Abstraction
#define BuzzerArrPort   P2OUT
#define BuzzerSel       P2SEL
#define BuzzerDir       P2DIR

#define Buzzer          0x04


extern void updateRGB(int RGB);
extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void clearConfig();
#endif



