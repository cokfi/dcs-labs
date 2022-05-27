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
  BuzzerSel |= Buzzer; // Set P2.2/Buzzer to TimerB output
  BuzzerDir |= Buzzer;

  // Keypad Setup
  KeypadIntSel &= ~IRQ;
  KeypadIntDir &= ~IRQ;
  
  KeypadSel = 0x00; // IO mode = 0
  KeypadDir = 0x0F; // input = 0, output = 1
  
  P2IFG = 0x00;
  
  
  _BIS_SR(GIE); // enable interrupts globally 
  // TODO - Delete
}                             

// DMA Configuration
void DMAConfig()
{
  DMACTL0 |= DMA1TSEL_7;
  DMACTL0 |= DMA0TSEL_1; // Use TACCR2 as Trigger
  DMA0CTL |= DMADT_4 + DMASRCINCR_3 + DMADSTBYTE + DMASRCBYTE;

  /* DMADT_4: Tranfer Mode = Repeated single transfer,
   * DMASRCINC_3: Increase source address for each transfer,
   * DMADSTBYTE: ,
   * DMASRCBYTE: */
}
// Timers congiguration 
void TIMERconfig(void)
{
  // TimerA Configuration
  TACTL |= TASSEL_2 + TACLR;          // SMCLK, clear TBR, up mode
  TACCR2 = 0x115; // Count to 325ms
  
  // TimerB Configuration
  TBCTL |= TBSSEL_1 + TBCLR;
  TBCCTL0 |= CCIE;
} 

void enableTransfersDMA()
{
  TACTL |= MC_1;
  TBCTL |= MC_1;
  DMA0CTL |= DMAIE + DMAEN;
}


void enableKeypad()
{
  P2IE |= IRQ;
}


// Start DMA Transfers
void startDMATransfers(void)
{
  TACCR2 = 0x155;
  TACCTL2 = OUTMOD_6;                       // TACCR2 toggle/set
}

// DMA Configurations
//void recordConfig(){
//
//  //int i = 0x03600;                              // Delay for needed ref start-up.
//  //while(i--){                               // See datasheet for details.
//  //TBCCR0 = 100;                             // Init TBCCR0 w/ sample prd
//  //TBCCR1 = 70;                              // Trigger for ADC12 SC
//  //TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0
//  //DMA0SA = (void (*)())&ADC12MEM0;          // Src address = ADC12 module
//  //DMA0DA = (void (*)())0x01500;             // Dst address = RAM memory
//  //DMA0SZ = 0x020;                           // Size in words
//  //DMACTL0 = DMA0TSEL_6;                     // ADC12IFGx triggers DMA0
//  //DMA0CTL = DMADSTINCR_3 + DMAIE + DMAEN;   // Config
//  //P5OUT |= 0x02;                            // Start recording and enter LPM0
//  //TBCTL = TBSSEL_2 + TBCLR;          // SMCLK, clear TBR, up mode
//  //__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
//  //TBCTL = 0;                                // Disable Timer_B
//  //P5OUT &= ~0x02;                           // Clear P5.1 (LED Off)
//  }
//}
//

 
             
             
            
  

