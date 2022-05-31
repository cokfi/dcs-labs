#ifndef _bsp_H_
#define _bsp_H_

//#include  <msp430g2553.h>          // MSP430x2xx
#include  <msp430xG46x.h>  // MSP430x4xx

/*
  Ports and Connections:

  1. PB0-PB2        => P1.0-P1.2 v
  2. LCD D4-D7      => P1.4-P1.7 v
  3. LCD Ctl Lines  => P2.5-P2.7 v
  4. Buzzer         => P2.2      v
  5. Keypad         => P10       v
  6. Keypad Int     => P2.1      v
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



extern void GPIOconfig(void);
extern void TIMERconfig(void);
extern void DMAConfig(void);
extern void enableTransfersDMA(void);
extern void startDMATransfers(void);
extern void stopTransfersDMA(void);
extern void enableKeypad();
extern void disableKeypadInterupts;
extern void enableKeypadInterupts;
//extern void recordConfig(void);
#endif



