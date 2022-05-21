#include  "../header/bsp.h"    // private library - BSP layer

// GPIO congiguration
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // LEDs 8-bit Array Port configuration
  LEDsArrPortSel &= ~0xFF;            // GPIO capability
  LEDsArrPortDir |= 0xFF;             // output dir
  LEDsArrPort = 0x00;				  // clear all LEDs
  
  // Switches Setup
  SWsArrPortSel &= ~0x0F;
  SWsArrPortDir &= ~0x0F;
  
  // PushButtons Setup
  PBsArrPortSel &= ~0xF0;
  PBsArrPortDir &= ~0xF0;
  PBsArrIntEdgeSel |= 0x30;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0xC0;         // pull-down mode
  PBsArrIntEn |= 0x70;
  PBsArrIntPend &= ~0xF0;            // clear pending interrupts 
  
  // Buzzer Setup
  BuzzerSel &= ~Buzzer;
  BuzzerDir |= Buzzer;

  _BIS_SR(GIE); // enable interrupts globally
}                             

// DMA Configuration
void DMAConfig(){

  DMACTL0 = DMA1TSEL_7;
  
  DMA0EN = 0;
  DMACTL0 = DMA0TSEL_1; // Use TACCR2 as Trigger
  DMA0CTL = DMADT_8 + DMASRCINC_3 + DMADSTBYTE + DMASRCBYTE;

}
// Timers congiguration 
void TIMERconfig(void){
  // TimerA Configuration
  TACTL = TASSEL_2 + TACLR;          // SMCLK, clear TBR, up mode
  TACCR2 = 0x115; // Count to 325ms
  
} 

void  nableTransfersDMA(){
  TACTL += MC_1;
  DMA0CTL += DMAIE + DMAREQ;
}

// ADC congiguration 
void ADCconfig(void){
	//write here ADC congiguration code
}              


void KeypadConfig(void){
  KeypadIntSel |= 0x02;
}

// Start DMA Transfers
void startDMATransfers(void){
  TACCR0 = ;
  TACCR2 = ;

  TACCTL2 = OUTMOD_6;                       // TACCR2 toggle/set

}

// DMA Configurations
void recordConfig(){
	volatile int i;
  ADC12MCTL0 = SREF_1 + INCH_10;            // Channel A10, Vref+
  ADC12IFG = 0;
  ADC12CTL1 = SHS_3 + CONSEQ_2;             // S&H TB.OUT1, rep. single chan
  ADC12CTL0 = REF2_5V + REFON + ADC12ON + ENC;    // VRef ADC12 on, enabled
  i = 0x03600;                              // Delay for needed ref start-up.
  while(i--);                               // See datasheet for details.
  TBCCR0 = 100;                             // Init TBCCR0 w/ sample prd
  TBCCR1 = 70;                              // Trigger for ADC12 SC
  TBCCTL1 = OUTMOD_7;                       // Reset OUT1 on EQU1, set on EQU0
  DMA0SA = (void (*)())&ADC12MEM0;          // Src address = ADC12 module
  DMA0DA = (void (*)())0x01500;             // Dst address = RAM memory
  DMA0SZ = 0x020;                           // Size in words
  DMACTL0 = DMA0TSEL_6;                     // ADC12IFGx triggers DMA0
  DMA0CTL = DMADSTINCR_3 + DMAIE + DMAEN;   // Config
  P5OUT |= 0x02;                            // Start recording and enter LPM0
  TBCTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, clear TBR, up mode
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
  ADC12CTL1 &= ~CONSEQ_2;                   // Stop conversion immediately
  ADC12CTL0 &= ~ENC;                        // Disable ADC12 conversion
  ADC12CTL0 = 0;                            // Switch off ADC12 & ref voltage
  TBCTL = 0;                                // Disable Timer_B
  P5OUT &= ~0x02;                           // Clear P5.1 (LED Off)
}
             

 
             
             
            
  

