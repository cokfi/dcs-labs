#include  "../header/halGPIO.h"     // private library - HAL layer

// System Configuration  
void sysConfig(void)
{

    GPIOconfig();
    TIMERconfig();
    lcd_init();
    clearLCD();
 
}
void sysConfigState1(void)
{
    TIMERconfig();
    DMAConfig();
    startRowLCD(0);
    lcd_puts("Recording...");
}
void sysConfigState2(void)
{
    TIMERconfig();
    DMAConfig();
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

// Port10/Keypad Interrupt Service Routine
#pragma vector = PORT2_VECTOR
__interrupt void Keypad_handler(void)
{
    keypadButton = -1;

    /* Search for pushed button row-by-row using running zero method:
     E(1110)
     D(1101)
     B(1011)
     7(0111)
     */
    // Check first Row
    P10OUT = 0x0E;
    if ((P10IN & 0x10) == 0)
        keypadButton = 0x0D;
    else if ((P10IN & 0x20) == 0)
        keypadButton = 0x0E;
    else if ((P10IN & 0x40) == 0)
        keypadButton = 0x00;
    else if ((P10IN & 0x80) == 0)
        keypadButton = 0x0F;

    // Check Second Row
    P10OUT = 0x0D;
    if ((P10IN & 0x10) == 0)
        keypadButton = 0x0C;
    else if ((P10IN & 0x20) == 0)
        keypadButton = 0x09;
    else if ((P10IN & 0x40) == 0)
        keypadButton = 0x08;
    else if ((P10IN & 0x80) == 0)
        keypadButton = 0x07;

    // Check Third Row
    P10OUT = 0x0B;
    if ((P10IN & 0x10) == 0)
        keypadButton = 0x0B;
    else if ((P10IN & 0x20) == 0)
        keypadButton = 0x06;
    else if ((P10IN & 0x40) == 0)
        keypadButton = 0x05;
    else if ((P10IN & 0x80) == 0)
        keypadButton = 0x04;

    // Check Fourth Row
    P10OUT = 0x07;
    if ((P10IN & 0x10) == 0)
        keypadButton = 0x0A;
    else if ((P10IN & 0x20) == 0)
        keypadButton = 0x03;
    else if ((P10IN & 0x40) == 0)
        keypadButton = 0x02;
    else if ((P10IN & 0x80) == 0)
        keypadButton = 0x01;

    delay(debounceVal);
    if (state == state1){
        //int newNote = recordNote();

        if(keypadButton != -1)
        {
            playNote(keypadButton);
            recorder[32-countingIndexRecord] = keypadButton;
            countingIndexRecord--;
        }



    }
    P10OUT = 0x00; // Reset rows to prepare for next interrupt
    KeypadIntPend &= ~IRQ;

    __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}

#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{
    DMA0CTL &= ~DMAIFG;                       // Clear DMA0 interrupt flag
    DMA1CTL &= ~DMAIFG;                       
    
    TBCTL &= ~MC_1; // Stop Timer
    //outNote = DMA0DA;
    __bic_SR_register_on_exit(LPM0_bits); // Exit LPMx, interrupts enabled
}

// ISR to execute when reaching 325 ms
#pragma vector = TIMERA1_VECTOR
__interrupt void timerA_ISR(void)
{
  if(state==state2)
  {
    //playNote(outNote);
      if(DMA0SZ <2)
      {
        TBCTL &= ~MC_1; // Stop Timer
        //TBCTL |= TBCLR;
      }
  }
  

//  else
//  {
//    //DMA0CTL |= DMAREQ;
//    //DMA1CTL |= DMAREQ;
//  }
  TACTL &= ~TAIFG;
   __bic_SR_register_on_exit(LPM0_bits); // Exit LPMx, interrupts enabled
}


//**************************************************************************************************






//TODO DELETE
// ISR to execute when reaching 325 ms
#pragma vector = TIMERB0_VECTOR
__interrupt void timerB_ISR(void)
{
    TBCTL &= ~TBIFG; // Clear interrupt flag
    BuzzerArrPort ^= Buzzer; //TODO Check if good
}


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