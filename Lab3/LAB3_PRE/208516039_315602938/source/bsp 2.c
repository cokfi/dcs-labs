#include  "../header/bsp.h"    // private library - BSP layer

// GPIO congiguration
void GPIOconfig(void)
{
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
//  // LEDs 8-bit Array Port configuration
//  LEDsArrPortSel &= ~0xFF;            // GPIO capability
//  LEDsArrPortDir |= 0xFF;             // output dir
//  LEDsArrPort = 0x00;				  // clear all LEDs
//

  
  // PushButtons Setup
  // TODO Check if good
  PBsArrPortSel &= ~0x07;            // P1.
  PBsArrPortDir &= ~0x07;            //
  
  
  //PBsArrIntEdgeSel |= 0x01;  	     // pull-up mode PB1
  //PBsArrIntEdgeSel &= ~0x06;         // pull-down mode PB2-3
  
  /* If PB0 Not Working
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode PB1-0
  PBsArrIntEdgeSel &= ~0x04;         // pull-down mode PB2
  */
  PBsArrIntEn |= 0x07;
  PBsArrIntPend &= ~0x07;            // clear pending interrupts 
  
  // Buzzer Setup
  BuzzerSel |= Buzzer; // Set P2.2/Buzzer to  output (not TimerB)
  BuzzerDir |= Buzzer;

  // Keypad Setup
  KeypadIntSel &= ~IRQ;
  KeypadIntDir &= ~IRQ;
  KeypadIntEdgeSel |= IRQ;
  KeypadSel = 0x00; // IO mode = 0
  KeypadDir = 0x0F; // input = 0, output = 1
  
  P2IFG = 0x00;
  
  
  _BIS_SR(GIE); // enable interrupts globally 
  // TODO - Delete
}                             

/* 
DMA Configuration 
*/
void DMAConfig()
{
  DMACTL0 &= ~DMAEN;
  DMACTL0 |= DMA0TSEL_7;
  //DMACTL0 |= DMA0TSEL_1; // Use TACCR2 as Trigger
  DMA0CTL |= DMADT_4 + DMASRCINCR_3;
  //DMA0CTL &= ~DMASRCBYTE + ~DMADSTBYTE;
  DMA0CTL |= DMASRCBYTE + DMADSTBYTE + DMAIE;
  
  
  /* DMADT_4: Tranfer Mode = Repeated single transfer,
   * DMASRCINC_3: Increase source address for each transfer,
   * DMADSTBYTE: 
   * DMASRCBYTE: */
}


/*
 Timers congiguration 
*/
void TIMERconfig(void)
{
  // TimerA Configuration
  TACTL |= TASSEL_1 +TACLR;          // SMCLK, clear TBR, up mode
  TACCR0 = 0x28A0; // Count to 325ms
  
  // TimerB Configuration
  TBCTL |= TBSSEL_2 + TBCLR;
  //TBCCTL0 |= CCIE;
} 


void enableTransfersDMA()
{
  
  DMACTL0 &= ~DMAEN;
  DMACTL0 |= DMA0TSEL_7;
  //DMACTL0 |= DMA0TSEL_1; // Use TACCR2 as Trigger
  DMA0CTL |= DMADT_4 + DMASRCINCR_3;
  DMA0CTL &= ~DMASRCBYTE + ~DMADSTBYTE;
  //DMA0CTL |= DMASRCBYTE + DMADSTBYTE;
  
  DMA1CTL |= DMADT_4 + DMASRCINCR_3;
  DMA1CTL &= ~DMASRCBYTE + ~DMADSTBYTE;
  
  //TBCTL |= MC_1;
  DMA0CTL |= DMAEN;
  DMA1CTL |= DMAEN;
  
  TACTL |= TAIE + TACLR + MC_1;
}

void stopTransfersDMA()
{
  TACTL &= ~TAIE;
  DMA0CTL &= ~DMAEN;
}
void clearConfig(){
    TBCTL = 0x00;
    TBCCTL1 = 0x00;
    TBCCR0 = 0x00;
    TBCCR1 = 0x00;
    TACTL = 0x00;
    TACCTL2= 0x00;
    TACCR0= 0x00;
    TACCR2= 0x00;
    DMACTL0= 0x00;
    DMA0CTL= 0x00;
}

void enableKeypad()
{
  P2IE |= IRQ;
}


// Start DMA Transfers
void startDMATransfers(void)
{
  TACCR2 = 0x5333;
  TACCTL2 = OUTMOD_6;                       // TACCR2 toggle/set
}

//void enableKeypadInterupts() {
//    KeypadIntEn |= IRQ; // Enable Keypad Interrupts
//}
//void disableKeypadInterupts() {
//    KeypadIntEn &= ~IRQ; // disable Keypad Interrupts
//}
             
            
  

