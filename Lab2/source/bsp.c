#include  "../header/bsp.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
    ADCArrPortSel &= ~0x08;
    ADCArrPortDir &= ~0x08; //input dir
    GeneratorDir &= ~0x10;//p2.4
    GeneratorDir|= 0x04;//p2.2
    GeneratorSel |=  0x14;//p2.4 P2.2
    ADCArrPortSel |=0x08;//INPUT

  
  // PushButtons Setup
  PBsArrPortSel &= ~0x07; //  PB : 0-2
  PBsArrPortDir &= ~0x07;
  PBsArrIntEdgeSel |= 0x03;  	     // pull-up mode
  PBsArrIntEdgeSel &= ~0x04;         // pull-down mode
  PBsArrIntEn = 0x07;
  PBsArrIntPend &= ~0xFF;            // clear pending interrupts 

  PB3ArrPortSel &= ~0x01; //  PB : 0-2
  PB3ArrPortDir &= ~0x01;
  PB3ArrIntEdgeSel &= ~0x01;         // pull-down mode
  PB3ArrIntEn |= 0x01;
  PB3ArrIntPend &= ~0xFF;            // clear pending interrupts 

  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
  
	//timer 1
  TA1CTL = TASSEL_2 + MC_2 + TACLR;        // SMCLK, Cont Mode: the timer counts up to 0FFFFh, reset TAR
  TA1CCTL2 = CAP + CM_2 + SCS + CCIS_0; // TA0CCR1 Capture mode; CCI1A; rising edge,Synnchronous capture, interrupt enable, CCIA (pin P2.4)
 //timer 0
  TA0CTL = TASSEL_2+ID_2 + MC_2 + TACLR;        // SMCLK,divide frequency by 8, Cont Mode: the timer counts up to 0FFFFh, reset TAR
  TA0CCTL2 = CM_2 + SCS;// compare mode, sync 
  TA0CCR1 = 0xffff;  
  TA0CCR0 = 0xffff;
  TA0CCR2 = 0xffff;
  TA0CCTL2 &= ~CCIE;
  TA1CCTL2 &= ~CCIE;

} 
//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
  ADC10CTL0 = ADC10SHT_1 + ADC10ON + ADC10IE;
  ADC10CTL1 = INCH_3;  
  ADC10CTL1 |= CONSEQ_2+ADC10SSEL_3+SHS_1; // input from  P1.3 (A3)
  ADC10AE0 |= 0x08;                     // P1.3 ADC on
}

//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void state1TimerConfig(void){




} 
void TIMERconfigState2(void){
  
}
           
             

 
             
             
            
  

