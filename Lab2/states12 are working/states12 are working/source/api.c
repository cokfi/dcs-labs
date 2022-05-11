#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer
char finStr[] = "Fin = ";
char frequencyStr[] ="00000"; // 20 to 20K Hz up to 5 chars
char hzStr[] = " Hz";
char timeElapsedStr[] = "00:00";

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
void 
displayFin(){
	//lcd_puts(finStr);
	int i;
        long int asistFrequency = REdge2-REdge1;
        if (asistFrequency>0){ // make sure overflow doesn't ruin calculation
					asistFrequency = (long int)((SMCLK_FREQUENCY/(asistFrequency))*1.095);
                                        //asistFrequency = frequency;
	for(i=4; i>=0; i--){
		frequencyStr[i] = asistFrequency%10 + 48 ;// assci values 48 = 0, 49 = 1 ...
		asistFrequency = asistFrequency/10;
        lcd_goto(6);
	lcd_puts(frequencyStr);
        lcd_puts(hzStr);
        }
        }
        /*else if (REdge2>0){
          frequency = (int)((SMCLK_FREQUENCY/(asistFrequency+0xffff))*1.085);
                                        asistFrequency =frequency;
	for(i=4; i>=0; i--){
		frequencyStr[i] = asistFrequency%10 + 48 ;// assci values 48 = 0, 49 = 1 ...
		asistFrequency = asistFrequency/10;
        lcd_goto(6);
	lcd_puts(frequencyStr);
        lcd_puts(hzStr);
        }
				
	
}*/
}
void displayTimeElapsed(int timeElapsed){
        lcd_clear();
	for(int i=4; i>=3; i--){
		timeElapsedStr[i] = timeElapsed%10 + 48 ;// assci values 48 = 0, 49 = 1 ...
		timeElapsed = timeElapsed/10;
	}
	lcd_puts(timeElapsedStr);
}

int calcFrequency3(int originFreq){
	long int asistFrequency = REdge2-REdge1;
        if (asistFrequency>0){ // make sure overflow doesn't ruin calculation
					asistFrequency = (long int)((SMCLK_FREQUENCY/(asistFrequency))*1.095);
					return asistFrequency;}
else return originFreq; 
}



 
  

