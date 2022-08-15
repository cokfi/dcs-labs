#include  "../header/halGPIO.h"     // private library - HAL layer
//-------------------------------------------------------------
//           globals
//-------------------------------------------------------------
const char stringThanks[] = { "Thanks\r\n" };
const char stringEnterDelay[] = { "Please enter the delay in ms\r\n" };
char stringDelay[16];
int isDelaySet;
int delayLength;
int  temporaryDelay=0; //a maximum of ??? seconds
unsigned int i; // counter for output string 
unsigned int j=0; // counter for input string/int identation 
unsigned int isDelayExpected = 0; // is delay input is expected to be sent from pc now (part of state 4)
int checkBug;
//-------------------------------------------------------------
//           system configurations
//-------------------------------------------------------------
void sysConfig(void)
{
    GPIOconfig();
    lcd_init();
 
}
//-------------------------------------------------------------
//           state1 configurations
//-------------------------------------------------------------
void sysConfigState1(void)
{
    TIMERconfig();
    lcd_clear();
    char finS[] = "Fin = ";
    lcd_puts(finS);

}
void sysConfigState2(void)
{
    TIMERconfig();
    lcd_clear();
    char timeElapsedS[] = "01:00";
	lcd_puts(timeElapsedS);
}
// Polling based Delay function
void delay(unsigned int t)
{  // t[msec]
    volatile unsigned int i;

    for (i = t; i > 0; i--);
}


// Enter from LPM0 mode
void enterLPM(unsigned char LPM_level)
{
    if (LPM_level == 0x00)
        __bis_SR_register(LPM0_bits + GIE); /* Enter Low Power Mode 0 */
    else if (LPM_level == 0x01)
        __bis_SR_register(LPM1_bits + GIE) ; /* Enter Low Power Mode 1 */
    else if (LPM_level == 0x02)
        __bis_SR_register(LPM2_bits + GIE); /* Enter Low Power Mode 2 */
    else if (LPM_level == 0x03)
        __bis_SR_register(LPM3_bits + GIE); /* Enter Low Power Mode 3 */
    else if (LPM_level == 0x04)
        __bis_SR_register(LPM4_bits + GIE); /* Enter Low Power Mode 4 */
}

// Enable interrupts
void enable_interrupts()
{
    _BIS_SR(GIE);
}

// Disable interrupts
void disable_interrupts()
{
    _BIC_SR(GIE);
}

void readVoltage()
{
    /* 
        ADC10CTL1:
        - INCH_1   to choose P1 as input to read from
        - CONSEQ_2 Repeat single channel mode
        

        ADC10CTL0:
        - ADC10SHT_3 Sample&Hold Time (Not sure about it)
        - ADC10ON    ADC is 'On' (Shocking!)
        - MSC        ADC continous automatically after first trigger 
        
        -
        Notes:
        - ADC10 is disabled in clearConfig()
        - To stop ADC reset the MSC

    */

    ADC10CTL1 = INCH_1  + CONSEQ_2;// P1 as input, repeat single channel
    ADC10CTL0 = ADC10SHT_3 + ADC10ON + MSC + ADC10IE;
    ADC10AE0 = 0x04;

    for (;;)
    {
        ADC10CTL0 |= ENC + ADC10SC; // Enable and start conversions
        __bis_SR_register(CPUOFF + GIE);   // LPM0, ADC10_ISR will force exit
    }
}


//-------------------------------------------------------------
// LCD
//-------------------------------------------------------------

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
  asm(" nop");
  asm(" nop");
  LCD_EN(0);
}
//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) asm(" nop"); // tha command asm("nop") takes raphly 1usec
	
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




//-------------------------------------------------------------
// Timer A0 interrupt service routine
//-------------------------------------------------------------
//state1: every timerDelayMs [ms] clear flag and getting out of sleep mode
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  TACTL &= ~TAIFG; 
  __bic_SR_register_on_exit(LPM0_bits); // Exit LPMx
}


//-------------------------------------------------------------
//           interrupt vector uartTx
//-------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCI0TX_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch (state)
    {
        case state4:
            if (isDelayExpected!=0){ // waiting for delay input 
                UCA0TXBUF = stringEnterDelay[i++];                 // TX next character
                if (i == sizeof stringEnterDelay - 1){              // TX over?
                    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
                }
            }
            else{                           // not waiting for delay input
                UCA0TXBUF = stringThanks[i++];
                if (i == sizeof stringThanks - 1)              // TX over?
                    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
            }

            break;
        default:
            UCA0TXBUF = stringThanks[i++];                 // TX next character
            if (i == sizeof stringThanks - 1)              // TX over?
                IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt

    }
}

//-------------------------------------------------------------
//           interrupt vector uartRx
//-------------------------------------------------------------
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
if (isDelayExpected != 1){ // expecting state to be chosen by the user 
    if (UCA0RXBUF == '1')                     // 'u' received?
    {
        state = state1;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '2')                     // 'u' received?
    {
        state = state2;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '3')                     // 'u' received?
    {
        state = state3;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '4')                     // 'u' received?
    {
        isDelayExpected = 1; // use uart input to get the Delay 
        state = state4;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringEnterDelay[i++];
    }
    else if (UCA0RXBUF == '5')                     // 'u' received?
    {
        state = state5;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '6')                     // 'u' received?
    {
        state = state6;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '7')                     // 'u' received?
    {
        state = state7;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '8')                     // 'u' received?
    {
        state = state8;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
    else if (UCA0RXBUF == '9')                     // 'u' received?
    {
        state = state9;
        i = 0;
        IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
        UCA0TXBUF = stringThanks[i++];
    }
}
else {                                     // expecting Delay to be chosen by the user
  if (UCA0RXBUF != '\n'){
      stringDelay[j] = UCA0RXBUF; //  add 10^j times the entered digit
    j++;
  }
  else       // end of string
  {
    delayLength = j;
    isDelaySet = 1;
    isDelayExpected = 0;
    i = 0;
    j = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
  }
}


      // Exit from a given LPM
    switch (lpm_mode)
    {
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


//-------------------------------------------------------------
// ADC10 interrupt service routine
//-------------------------------------------------------------

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(ADC10_VECTOR))) ADC10_ISR (void)
#else
#error Compiler not supported!
#endif
{
    volatge[2] = ADC10MEM[9] + '0';
    volatge[1] = ADC10MEM[8] + '0';
    volatge[0] = ADC10MEM[7] + '0';

    lcd_puts(voltage);
    __bic_SR_register_on_exit(CPUOFF); // Clear CPUOFF bit from 0(SR)
}
