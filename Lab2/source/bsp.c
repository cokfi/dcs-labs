#include  "../header/bsp.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
   
  // LEDs 8-bit Array Port configuration
  //LEDsArrPortSel &= ~0xFF;            // GPIO capability
  //LEDsArrPortDir |= 0xFF;             // output dir
  //LEDsArrPort = 0x00;				  // clear all LEDs
  
  // Switches Setup
  //SWsArrPortSel &= ~0x0F;
  //SWsArrPortDir &= ~0x0F;
  
  // PushButtons Setup
  PBsArrPortSel &= ~0x07; // 3 PB : 0-2
  PBsArrPortDir &= ~0x07;
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x04;         // pull-down mode
  PBsArrIntEn |= 0x07;
  PBsArrIntPend &= ~0xFF;            // clear pending interrupts 

  
  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
  //timer 0
  TA0CTL = TASSEL_2 + MC_2 + TACLR;        // SMCLK, Cont Mode: the timer counts up to 0FFFFh, reset TAR
	//timer 1
  TA1CTL = TASSEL_2 + MC_2 + TACLR;        // SMCLK, Cont Mode: the timer counts up to 0FFFFh, reset TAR
  TA1CCTL2 = CAP + CM_1 + SCS + CCIS_0; // TA0CCR1 Capture mode; CCI1A; rising edge,Synnchronous capture, interrupt enable, CCIA (pin P2.4)
  TA1CCTL2 &= ~CCIE;

} 
//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	//write here ADC congiguration code
}

//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void state1TimerConfig(void){




} 
void TIMERconfigState2(void){
  
}
           
             

 
             
             
            
  

