#include  "../header/halGPIO.h"     // private library - HAL layer
unsigned int REdge1, REdge2;
unsigned long int frequency=0;
int isFirstEdge = 0; // active low
unsigned char count=0x00;
char timePrint[2];
int analog1;
int analog2;
int analog3;
int analog4;
int analogFlag = 0;
int analogAvg = 0;
//--------------------------------------------------------------------
//             System Configuration  
//--------------------------------------------------------------------
void sysConfig(void){ 
	GPIOconfig();
	TIMERconfig();
	lcd_init();
}
void configState1(void){
        TA0CCTL0 &= ~CCIE;
        TA1CCTL2 |= CCIE; // enable interupts Timer1
	lcd_clear();
        char finS[] = "Fin = ";
	lcd_puts(finS);
        
}

void configState2(void){
        TA0CCTL0 |= CCIE;//overflow only
        TA1CCTL2 &= ~CCIE;; // disable interupts Timer1
	lcd_clear();
        char timeElapsedS[] = "01:00";
	lcd_puts(timeElapsedS);
}
void configState3(void){
        ADCconfig();
	TA1CTL= TASSEL_2+ MC_1 ;
	TA1CCTL1 = OUTMOD_4; //toggle
	TA0CTL = TASSEL_2+MC_1; 
        TA0CCR0 = 0x4000;
	TA0CCR1 = 	0x5;
	TA0CCTL1 = OUTMOD_4;

}
void sing(void){
	
}
//******************************************************************
// initialize the LCD
//******************************************************************
void lcd_init(void){
  
	char init_value;

	if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
        else init_value = 0x3F;
	
  	
	LCD_RS_DIR(OUTPUT_PIN);
	LCD_EN_DIR(OUTPUT_PIN);
	LCD_RW_DIR(OUTPUT_PIN);
    LCD_DATA_DIR |= OUTPUT_DATA;
	LCD_C_SEL &= ~0xE0;
	LCD_D_SEL &= ~0xF0;
    LCD_RS(0);
	LCD_EN(0);
	LCD_RW(0);
        
	DelayMs(15);
    LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayMs(5);
    LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayUs(200);
    LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	
	if (LCD_MODE == FOURBIT_MODE){
		LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
		lcd_strobe();
		lcd_cmd(0x28); // Function Set
	}
        else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots 
	
	lcd_cmd(0xF); //Display On, Cursor On, Cursor Blink
	lcd_cmd(0x1); //Display Clear
	lcd_cmd(0x6); //Entry Mode
	lcd_cmd(0x80); //Initialize DDRAM address to zero
}    
//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s){
  
	while(*s)
		lcd_data(*s++);
}
//******************************************************************
// lcd strobe functions
//******************************************************************
void lcd_strobe(){
  LCD_EN(1);
  asm("nop");
  asm("nop");
  LCD_EN(0);
}
//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm("nop"); // tha command asm("nop") takes raphly 1usec
	
} 
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec
	
}    
//******************************************************************
// send a command to the LCD
//******************************************************************
void lcd_cmd(unsigned char c){
  
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	if (LCD_MODE == FOURBIT_MODE)
	{
		LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
		lcd_strobe();
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
    		LCD_DATA_WRITE |= (c & (0x0F)) << LCD_DATA_OFFSET;
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
}
//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_data(unsigned char c){
        
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_DATA_WRITE &= ~OUTPUT_DATA;       
	LCD_RS(1);
	if (LCD_MODE == FOURBIT_MODE)
	{
    		LCD_DATA_WRITE &= ~OUTPUT_DATA;
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;  
		lcd_strobe();		
                LCD_DATA_WRITE &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= (c & 0x0F) << LCD_DATA_OFFSET; 
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
          
	LCD_RS(0);   
}
/*
//--------------------------------------------------------------------
// 				Print Byte to 8-bit LEDs array 
//--------------------------------------------------------------------
void print2LEDs(unsigned char ch){
	//LEDsArrPort = ch;
}    
//--------------------------------------------------------------------
//				Clear 8-bit LEDs array 
//--------------------------------------------------------------------
void clrLEDs(void){
	//LEDsArrPort = 0x000;
}  
//--------------------------------------------------------------------
//				Toggle 8-bit LEDs array 
//--------------------------------------------------------------------
void toggleLEDs(char ch){
	//LEDsArrPort ^= ch;
}
//--------------------------------------------------------------------
//				Set 8-bit LEDs array 
//--------------------------------------------------------------------
void setLEDs(char ch){
	//LEDsArrPort |= ch;
}
//--------------------------------------------------------------------
//				Read value of 4-bit SWs array 
//--------------------------------------------------------------------
unsigned char readSWs(void){
	unsigned char ch;
	
	ch = PBsArrPort;
	ch &= SWmask;     // mask the least 4-bit
	return ch;
}
//---------------------------------------------------------------------
//             Increment / decrement LEDs shown value 
//---------------------------------------------------------------------
void incLEDs(char val){
	LEDsArrPort += val;
}
*/
//---------------------------------------------------------------------
//            Polling based Delay function
//---------------------------------------------------------------------
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}

//---------------------------------------------------------------------
//            Enter from LPM0 mode
//---------------------------------------------------------------------
void enterLPM(unsigned char LPM_level){
	if (LPM_level == 0x00) 
	  _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01) 
	  _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02) 
	  _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
	else if(LPM_level == 0x03) 
	  _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04) 
	  _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
}
//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}
//*********************************************************************
//            Port2 Interrupt Service Rotine
//*********************************************************************
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){
   
	delay(debounceVal);
//---------------------------------------------------------------------
//            selector of transition between states
//---------------------------------------------------------------------
	if(PBsArrIntPend & PB0){
	  state = state1;
	  PBsArrIntPend &= ~PB0;
	  initState = 0; 
        }
        else if(PBsArrIntPend & PB1){
	  state = state2;
	  PBsArrIntPend &= ~PB1; 
	  initState = 0; 
        }
	else if(PBsArrIntPend & PB2){ 
	  state = state3;
	  PBsArrIntPend &= ~PB2;
	  initState = 0; 
        }
//---------------------------------------------------------------------
//            Exit from a given LPM 
//---------------------------------------------------------------------	
        switch(lpm_mode){
		case mode0:
		 LPM0_EXIT; // must be called from ISR only
		 break;
		 
		case mode1:
		 LPM1_EXIT; // must be called from ISR only
		 break;
		 
		case mode2:
		 LPM2_EXIT; // must be called from ISR only
		 break;
                 
         case mode3:
		 LPM3_EXIT; // must be called from ISR only
		 break;
                 
         case mode4:
		 LPM4_EXIT; // must be called from ISR only
		 break;
	}
        
}
/*
//---------------------------------------------------------------------	
// TA1 Interrupt vector, the code is based on ta_21.c (hanan reference code)
//---------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A1_VECTOR))) TIMER0_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(TA1IV,0x0A))
  {
    case  TA1IV_NONE: break;              // Vector  0:  No interrupt
    case  TA1IV_TACCR2:                   // Vector  2:  TACCR2 CCIFG
            // Rising Edge was captured
            if (!isFirstEdge)
            {
                REdge1 = TA1CCR2;
                isFirstEdge++;
            }
            else //second edge
            {
                REdge2 = TA1CCR2;
                isFirstEdge=0;
				
                LPM0_EXIT;
				//__bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
            }
	default: 	break;
  }
}*/
//---------------------------------------------------------------------	
// TA1 Interrupt vector, the code is based on ta_21.c (hanan reference code)
//---------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A1_VECTOR))) TIMER1_A1_ISR (void)
#else
#error Compiler not supported!
#endif
{ 

  switch(__even_in_range(TA1IV,0x0A))
  {
    case  TA1IV_NONE: break;              // Vector  0:  No interrupt
    case  TA1IV_TACCR2:                   // Vector  2:  TACCR2 CCIFG
            // Rising Edge was captured
            if (!isFirstEdge)
            {
                REdge1 = TA1CCR2;
                isFirstEdge++;
            }
            else //second edge
            {
                REdge2 = TA1CCR2;
                isFirstEdge=0;
				/*if (REdge2>REdge1){ // make sure overflow doesn't ruin calculation
					frequency = SMCLK_FREQUENCY/(REdge2-REdge1);
				}*/
                LPM0_EXIT;
				//__bic_SR_register_on_exit(LPM0_bits + GIE);  // Exit LPM0 on return to main
            }
	default: 	break;
  }
}

//---------------------------------------------------------------------	
// TA0 Interrupt vector, the code is based on ta_21.c (hanan reference code)
//---------------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  //if (TA0IV>0x0){
  if (P2OUT&0x04){
    P2OUT &= ~0x04; // PWM
  }
  else{
     P2OUT |= 0x04;} // PWM 
	LPM0_EXIT;
  //}
  /*switch(__even_in_range(TA0IV,0x0F))
  {
    case  0xA:                   // Vector  2:  Timer overflow
             LPM0_EXIT;
            
	default: 	break;
  }*/
}
//adc Interrupt vector
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){

  switch(analogFlag){
    case 0:
        analog1 = ADC10MEM;
        analogFlag++;
        break;
    case 1:
        analog2 = ADC10MEM;
        analogFlag++;
        break;
    case 2:
        analog3 = ADC10MEM;
        analogFlag++;
        break;
    case 3:
        analog4 = ADC10MEM;
        analogAvg = (analog1 + analog2 + analog3 + analog4)/4;
        analogFlag = 0;
        TA1CCR0 = -analogAvg/3+500;
        break;
  }
 LPM0_EXIT;
} 
/*
//---------------------------------------------------------------------	
//WD Interrupt vector
//---------------------------------------------------------------------

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) WDT_ISR (void)
#else
#error Compiler not supported!
#endif
{
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
} 
*/