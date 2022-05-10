#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer


//-------------------------------------------------------------
//            Print SWs value onto LEDs
//-------------------------------------------------------------
void printSWs2LEDs(void){
	unsigned char ch;
	
	ch = readSWs();
	print2LEDs(ch);
}
//--------------------------------------------------------------------
//            Print array to LEDs array with rate of LEDs_SHOW_RATE
//--------------------------------------------------------------------            
void printArr2SWs(char Arr[], int size, unsigned int rate){
	unsigned int i;
	
	for(i=0; i<size; i++){
		print2LEDs(Arr[i]);
		delay(rate);
	}
}
void displayFin(){
	lcd_puts(finStr);
	int i;
	int asistFrequency =frequency;
	for(i=4; i>=0; i--){
		frequencyStr[i] = asistFrequency%10 + 48 ;// assci values 48 = 0, 49 = 1 ...
		asistFrequency = asistFrequency/10;
	lcd_puts(frequencyStr);
	lcd_puts(hzStr);
}
}



 
  

