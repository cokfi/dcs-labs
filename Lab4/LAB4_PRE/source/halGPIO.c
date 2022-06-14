#include  "../header/halGPIO.h"     // private library - HAL layer
//-------------------------------------------------------------
//           globals
//-------------------------------------------------------------
const char stringThanks[] = { "Thanks\r\n" };
const char stringEnterDelay[] = { "Please enter the delay in ms\r\n" };
int  temporaryDelay=0; //a maximum of ??? seconds
unsigned int i; // counter for output string 
unsigned int j=0; // counter for input string/int identation 
unsigned int isDelayExpected = 0; // is delay input is expected to be sent from pc now (part of state 4)
//-------------------------------------------------------------
//           system configurations
//-------------------------------------------------------------
void sysConfig(void)
{

    GPIOconfig();
    //TIMERconfig();
    lcd_init();
    clearLCD();
 
}
//-------------------------------------------------------------
//           state1 configurations
//-------------------------------------------------------------
void sysConfigState1(void)
{
    TIMERconfig();
    clearLCD();

}
void sysConfigState2(void)
{
    TIMERconfig();
    startRowLCD(0);
    lcd_puts("Recording...");
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
    temporaryDelay += ((int)UCA0RXBUF)*(10*j); //  add 10*j times the entered digit 
    j++;
  }
  else       // end of string
  {
    timerDelayMs = temporaryDelay;
    temporaryDelay = 0;    
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
