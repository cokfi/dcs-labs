#include  "../header/halGPIO.h"     // private library - HAL layer
//-------------------------------------------------------------
//           globals
//-------------------------------------------------------------
const char string1[] = { "Hello World\r\n" };
unsigned int i;
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


/*
// Port1 Interrupt Service Routine
#pragma vector=PORT1_VECTOR
__interrupt void PBs_handler(void)
{
    delay(debounceVal);

    if (PBsArrIntPend & PB0)
    {
        state = state1;
        PBsArrIntPend &= ~PB0;
    }
    else if (PBsArrIntPend & PB1)
    {
        state = state2;
        PBsArrIntPend &= ~PB1;
    }
    else if (PBsArrIntPend & PB2)
    {
        if (state == state2)
        {
            menuIndex = menuIndex + 1;
            if(menuIndex>4){
                menuIndex = 0;
            }
            //showMenu();
        }

        PBsArrIntPend &= ~PB2;
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
*/


//**************************************************************************************************




//-------------------------------------------------------------
// Timer A0 interrupt service routine
//-------------------------------------------------------------

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
//TODO DELETE
// ISR to execute when reaching 325 ms
//-------------------------------------------------------------
//           interrupt vector TIMERA0
//-------------------------------------------------------------
//#pragma vector = TIMERB0_VECTOR
//__interrupt void timerB_ISR(void)
//{
//    TBCTL &= ~TBIFG; // Clear interrupt flag
//
//}

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
  UCA0TXBUF = string1[i++];                 // TX next character

  if (i == sizeof string1 - 1)              // TX over?
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
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

  if (UCA0RXBUF == '1')                     // 'u' received?
  {
    state = state1;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '2')                     // 'u' received?
  {
    state = state2;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '3')                     // 'u' received?
  {
    state = state3;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '4')                     // 'u' received?
  {
    isTimerDelayUartInput = 1; // use uart input to get the Delay 
    state = state4;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '5')                     // 'u' received?
  {
    state = state5;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '6')                     // 'u' received?
  {
    state = state6;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '7')                     // 'u' received?
  {
    state = state7;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '8')                     // 'u' received?
  {
    state = state8;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
  }
  else if (UCA0RXBUF == '9')                     // 'u' received?
  {
    state = state9;
    i = 0;
    IE2 |= UCA0TXIE;                        // Enable USCI_A0 TX interrupt
    UCA0TXBUF = string1[i++];
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
