#include  "../header/bsp.h"    // private library - BSP layer

//-----------------------------------------------------------------------------  
//           GPIO congiguration
//-----------------------------------------------------------------------------
void GPIOconfig(void){
 // volatile unsigned int i; // in case of while loop usage
  
  WDTCTL = WDTHOLD | WDTPW;		// Stop WDT
<<<<<<< HEAD
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

=======
   
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
  
>>>>>>> d65fd191b344dff7b6d5022cfe36123d84261ea7
  _BIS_SR(GIE);                     // enable interrupts globally
}                             
//------------------------------------------------------------------------------------- 
//            Timers congiguration 
//-------------------------------------------------------------------------------------
void TIMERconfig(void){
	
	//write here timers congiguration code
} 
//------------------------------------------------------------------------------------- 
//            ADC congiguration 
//-------------------------------------------------------------------------------------
void ADCconfig(void){
	
	//write here ADC congiguration code
}              

           
             

 
             
             
            
  

