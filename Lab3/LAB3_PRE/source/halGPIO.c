#include  "../header/halGPIO.h"     // private library - HAL layer

// System Configuration  
void sysConfig(void)
{

    GPIOconfig();
    TIMERconfig();
    DMAConfig();
    lcd_init();
    clearLCD();
 
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
        _BIS_SR(LPM0_bits); /* Enter Low Power Mode 0 */
    else if (LPM_level == 0x01)
        _BIS_SR(LPM1_bits); /* Enter Low Power Mode 1 */
    else if (LPM_level == 0x02)
        _BIS_SR(LPM2_bits); /* Enter Low Power Mode 2 */
    else if (LPM_level == 0x03)
        _BIS_SR(LPM3_bits); /* Enter Low Power Mode 3 */
    else if (LPM_level == 0x04)
        _BIS_SR(LPM4_bits); /* Enter Low Power Mode 4 */
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

void playNote(int note)
{
   static const int tbNoteVals[] = {0x3EA,0x3B2,0x37D,0x34B,0x31C,0x2EF,0x2C4,0x29D,0x277,0x254,0x233,0x212,0x1F5};
  
   if((note<0) || (note>0xC))
    {
    return;
    }
    TBCCR0 = tbNoteVals[note];
    TBCCR1 = TBCCR0 >> 1; // TBCCR2 = TBCCR0/2 for 50% Duty Cycle
    TBCCTL1 = OUTMOD_7;                       // CCR2 reset/set

    TBCTL |= TBCLR;
    TBCTL |= TBSSEL_2 + MC_1; // Start Timer in up-mode
    
    delay(65000);

    TBCTL &= ~MC_1; // Stop Timer
    
}

// Record SingleNote and Play to buzzer
int recordNote()
{
    KeypadIntEn |= IRQ; // Enable Keypad Interrupts
    enterLPM(lpm_mode); // Enter LPM0
    // Wait for keypadInterrupt...
    return keypadButton;
}

// Display Menu of songs to play
int getSongChoice()
{
    int ret;
    int chosen = 0;
    lcd_init();
    keypadButton = -1;
    while (!chosen)
    {
        
        showMenu();
        enableKeypad();
        enable_interrupts();
        enterLPM(lpm_mode); // Enter LPM and wait for keypad interrupt (User Choice)
        showMenu();
        switch (keypadButton)
        {
        case 1:
            chosen = 1;
            ret = 1;
            break;
        case 2:
            chosen = 1;
            ret = 2;
            break;
        case 3:
            chosen = 1;
            ret = 3;
            break;
         case 4:
            chosen = 1;
            ret = 4;
            break;
        case -1:
            break;
        default:
            showInvalidChoiceMsg();
            break;
        }// Switch
    }// While
    return ret;
}

// Show menu based on index (menuIndex)
void showMenu()
{
    clearLCD();
    char *row1;
    char *row2;

    switch (menuIndex)
    {
    case 0:
      row1 = "Choose Song:";
        row2 = "1. Song1";
        break;

    case 1:
        row1 = "1. Song1";
        row2 = "2. Song2";
        break;
    case 2:
        row1 = "2. Song2";
        row2 = "3. Song3";
        break;
    case 3:
        row1 = "3. Song3";
        row2 = "4. Recorder";
        break;

    default:
        break;
    }
    
    startRowLCD(0);
    lcd_puts(row1);
    startRowLCD(1);
    lcd_puts(row2);

}

// Show "Invalid Choice Message"
void showInvalidChoiceMsg()
{
    clearLCD();
    startRowLCD(0);
    lcd_puts("Invalid Choice");
    delay(100);
}

// Play Song
/*void playSong(int song[], int size)
{
    DMA0SZ = size;
    //__data16_write_addr((unsigned short) &DMA0SA, (unsigned short) song); // Ignore
    //__data16_write_addr((unsigned short) &DMA0DA, (unsigned int) &outNote); // Ignore
    DMA0SA = (int)song;
    DMA0DA = (int)&outNote;

    // Start DMA
    int i = size;
    

     //TESTING
    
    enableTransfersDMA();
    while (DMA0SZ)
    {
        
        //playNote(outNote);
        enterLPM(lpm_mode);
        i--;
    }
    stopTransfersDMA();
    return;
}*/


void playSong(int song[], int size)
{
  static const int tbNoteVals[] = {0x3EA,0x3B2,0x37D,0x34B,0x31C,0x2EF,0x2C4,0x29D,0x277,0x254,0x233,0x212,0x1F5,};
  int tbccr0Vals[100];
  int tbccr1Vals[100];
  
  DMA0SZ = size;
  DMA1SZ = size;
  
  __data16_write_addr((unsigned short) &DMA0SA, (unsigned short) tbccr0Vals); // Ignore
  __data16_write_addr((unsigned short) &DMA1SA, (unsigned short) tbccr1Vals); // Ignore
  __data16_write_addr((unsigned short) &DMA0DA, (unsigned int) &TBCCR0); // Ignore
  __data16_write_addr((unsigned short) &DMA1DA, (unsigned int) &TBCCR1); // Ignore
  //DMA0SA = (int)tbccr0Vals;
  //DMA1SA = (int)tbccr1Vals;
  int i;
  for(i=0;i<size;i++)
  {
    tbccr0Vals[i]= tbNoteVals[song[i]];
    
    tbccr1Vals[i]= tbNoteVals[song[i]]>>1;
  }
  //DMA0DA = (int)&TBCCR0;
  //DMA1DA = (int)&TBCCR1;
  
      //TESTING
  TBCCTL1 = OUTMOD_7;                       // CCR2 reset/set

  TBCTL |= TBCLR;
  TBCTL |= TBSSEL_2 + MC_1; // Start Timer in up-mode

  enableTransfersDMA();
  DMA1CTL |= DMAREQ;
  DMA0CTL |= DMAREQ;
  while(DMA0SZ)
  { 
    /*if(DMA0SZ == 1)
    {
      stopTransfersDMA();
      return;
    }*/
    DMA1CTL |= DMAREQ;
    DMA0CTL |= DMAREQ;
   
    enterLPM(lpm_mode);
  }
  
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
    
  }
  
  if(DMA0SZ == 0)
  {
    TBCTL &= ~MC_1; // Stop Timer
    //TBCTL |= TBCLR;
  }
  else
  {
    //DMA0CTL |= DMAREQ;
    //DMA1CTL |= DMAREQ;
  }
  TACTL &= ~TAIFG;
   __bic_SR_register_on_exit(LPM0_bits); // Exit LPMx, interrupts enabled
}









//TODO DELETE
// ISR to execute when reaching 325 ms
#pragma vector = TIMERB0_VECTOR
__interrupt void timerB_ISR(void)
{
    TBCTL &= ~TBIFG; // Clear interrupt flag
    BuzzerArrPort ^= Buzzer; //TODO Check if good
}
