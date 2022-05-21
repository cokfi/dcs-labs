#include  "../header/halGPIO.h"     // private library - HAL layer


// System Configuration  
void sysConfig(void){ 
	GPIOconfig();
	TIMERconfig();
	ADCconfig();
}

// Recording Configuration
/*	Params:
			func = 0 => Configure for Recording 
	  	func = 1 => Configure for Playing
*/
void functionConfig(int func){
	switch (func)
	{
	case 0:
		recordConfig();
		break;
	
	case 1:
		playerConfig();
		break;

	default:
		return;
		break;
	}
}

// Polling based Delay function
void delay(unsigned int t){  // t[msec]
	volatile unsigned int i;
	
	for(i=t; i>0; i--);
}

// Enter from LPM0 mode
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

// Enable interrupts
void enable_interrupts(){
  _BIS_SR(GIE);
}

// Disable interrupts
void disable_interrupts(){
  _BIC_SR(GIE);
}

void playNote(char note){
		switch (not)
		{
		case '0':
			TBCCR0 = 32;
			break;
		case '1':
			TBCCR0 = 30;
			break;
		case '2':
			TBCCR0 = 28;
			break;
		case '3':
			TBCCR0 = 26;
			break;
		case '4':
			TBCCR0 = 25;
			break;
		case '5':
			TBCCR0 = 23;
			break;
		case '6':
			TBCCR0 = 22;
			break;
		case '7':
			TBCCR0 = 21;
			break;
		case '8':
			TBCCR0 = 20;
			break;
		case '9':
			TBCCR0 = 19;
			break;
		case 'A':
			TBCCR0 = 18;
			break;
		case 'B':
			TBCCR0 = 17;
			break;
		case 'C':
			TBCCR0 = 16;
			break;
		default:
			break;
		}// Switch

		TBCCR2 = TBCCR0 << 2; // TBCCR2 = TBCCR0/2 for 50% Duty Cycle
		TBCCTL2 = OUTMOD_7;                       // CCR2 reset/set

		TBCTL = MC_1; // Start Timer in up-mode
		delay(300);
}

// Record SingleNote and Play to buzzer
char recordNote(){
	KeypadIntEn |= IRQ; // Enable Keypad Interrupts
	enterLPM(lpm_mode); // Enter LPM0, wait for keypadInterrupt

	return keypadButton;
}

// Display Menu of songs to play
int getSongChoice(){
	int chosen = 0;
	lcd_init();

	while(!chosen){
		displaySongOptions();
		enterLPM(lpm_mode); // Enter LPM and wait for keypad interrupt (User Choice)

		switch (keypadButton)
		{
		case '1':
			return 1;
			chosen = 1;
			break;
		case '2':
			return 2;
			chosen = 1;
			break;
		case '3':
			return 3;
			chosen = 1;
			break;
		default:
			showInvalidChoiceMsg();
			break;
		}
	}
}


// Show menu based on index (menuIndex)
void showMenu(){
	clearLCD();
	char *row1;
	char *row2;


	switch (menuIndex%4)
	{
	case 0:
		row1 = "Please choose an option:";
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
	startRowLCD(0);
	lcd_puts(row2);

}

// Show "Invalid Choice Message"
void showInvalidChoiceMsg(){
	clearLCD();
	startRowLCD(0);
	lcd_puts("Invalid Choice");
	delayMs(100);
}

// Play Song
void playSong(int* song, int size){
	
	DMA0SA0 = &song;
	DMA0DA0 = &outNote;
	
	// Start DMA
	while (int i = 0; i < size;i++){
		enableTransfersDMA();
		enterLPM(lpm_mode);
		playNote(outNote);
	}
}
// Port1 Interrupt Service Routine
#pragma vector=PORT1_VECTOR
  __interrupt void PBs_handler(void){
   
	delay(debounceVal);

	if(PBsArrIntPend & PB0){
	  state = state1;
	  PBsArrIntPend &= ~PB0;
        }
  else if(PBsArrIntPend & PB1){
	  state = state2;
	  PBsArrIntPend &= ~PB1; 
        }
	else if(PBsArrIntPend & PB2){
		if(state == state2){
			menuIndex++;
			showMenu();
		}

		PBsArrIntPend &= ~PB2;
				}		

		// Exit from a given LPM 
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
 
// Port10/Keypad Interrupt Service Routine
#pragma vector = PORT2_VECTOR
__interrupt void Keypad_handler(void){
	keypadButton = 'K';

	/* Search for pushed button row-by-row using running zero method: 
		 E(1110)  
		 D(1101)  
		 B(1011) 
		 7(0111) 
		 */
	// Check first Row 
	P10OUT = 0x0E; 
	if((P10IN & 0x10 == 0))					keypadButton = 'D';
	else if((P10IN & 0x10 == 0))		keypadButton = 'E';
	else if((P10IN & 0x10 == 0))		keypadButton = '0';
	else if((P10IN & 0x10 == 0))		keypadButton = 'F';

	// Check Second Row 
	P10OUT = 0x0D; 
	if((P10IN & 0x10 == 0))					keypadButton = 'C';
	else if((P10IN & 0x10 == 0))		keypadButton = '9';
	else if((P10IN & 0x10 == 0))		keypadButton = '8';
	else if((P10IN & 0x10 == 0))		keypadButton = '7';

	// Check Third Row 
	P10OUT = 0x0B; 
	if((P10IN & 0x10 == 0))					keypadButton = 'B';
	else if((P10IN & 0x10 == 0))		keypadButton = '6';
	else if((P10IN & 0x10 == 0))		keypadButton = '5';
	else if((P10IN & 0x10 == 0))		keypadButton = '4';

	// Check Fourth Row 
	P10OUT = 0x07; 
	if((P10IN & 0x10 == 0))					keypadButton = 'A';
	else if((P10IN & 0x10 == 0))		keypadButton = '3';
	else if((P10IN & 0x10 == 0))		keypadButton = '2';
	else if((P10IN & 0x10 == 0))		keypadButton = '1';

	delay(debounceVal);

	P10OUT = 0x00; // Reset rows to prepare for next interrupt
	KeypadIntPort &= ~KeypadIntPend;

	__bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}

#pragma vector = DMA_VECTOR
__interrupt void DMA_ISR(void)
{
  DMA0CTL &= ~DMAIFG;                       // Clear DMA0 interrupt flag
	outNote = &DMA0DA;
	__bic_SR_register_on_exit(LPM0_bits); // Exit LPMx, interrupts enabled
}

// ISR to execute when reaching 325 ms
#pragma vector = TIMERA0_VECTOR
__interrupt void timerA_ISR(void){
	  TACTL = TACLR;          // clear TBR
}

// ISR to execute when reaching 325 ms
#pragma vector = TIMERB0_VECTOR
__interrupt void timerB_ISR(void){
	BuzzerArrPort ^= Buzzer; //TODO Check if good
}