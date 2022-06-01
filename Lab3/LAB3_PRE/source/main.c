#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

/* Follow This Link for Code flow Diagrams: 
	https://www.figma.com/file/aG8p1A8kZobp6yjx4eOLuu/Untitled?node-id=5%3A157 
*/


//#define SONG1_SIZE 54
//#define SONG2_SIZE 47
//#define SONG3_SIZE 40
#define RECORD_SIZE 32


enum FSMstate state;
enum SYSmode lpm_mode;

// Note: song sizes are defined in halGPIO.h
int keypadButton;
int song1[SONG1_SIZE] ={2,7,7,7,2,4,4,2,11,11,9,9,7,2,7,7,7,2,4,4,2,11,11,9,9,7,2,7,7,7,2,7,7,7,7,7,7,2,7,7,7,2,7,7,7,2,4,4,2,11,11,9,9,7}; // Uncle Moshe
int song2[SONG2_SIZE] ={0,5,9,0,5,9,9, 7,7,7,7,9,10,10,10,12,10,9,7,9,9,9,9,5,7,9, 10,10,10,12,10,10, 9,5,9,12,12, 0,4,7,10,9,7,5,5,5,5}; // Our Auto
int song3[SONG3_SIZE] ={4,7,4,4,7,4,12,11,9,7,5,2,5,9,7,7,5,4,2,0,4,7,4,4,7,4,12,11,9,7,5,2,5,9,7,7,5,4,2,0}; // Hands Up!
int recorder[RECORD_SIZE];
int initState = 1;
unsigned int countingIndexRecord = 32; //32 notes to play

void main(void)
{
	state = state0;				// start in idle state on RESET
	lpm_mode = mode0;     // start in idle state on RESET
	sysConfig();
  while(1)
	{
		switch(state)
		{
	  	case state0:
    		enterLPM(lpm_mode);
			break;
	  	case state1:
				//disable_interrupts();
	  	        if (initState >0){
	  	            clearConfig();
	  	            sysConfigState1();
	  	            initState = 0;
	  	        }
	  	        enableKeypad();
	  	        enterLPM(lpm_mode);
	  	        if (countingIndexRecord< 1){ //go to sleep
	  	            state = state0;
	  	          //disableKeypadInterupts();
	  	        }
	  	        if (state!= state1){
                    initState = 1;
                    countingIndexRecord = 32;
	  	        }
				//enable_interrupts();
				break;
	  	case state2:
				//disable_interrupts();
	  	        if (initState >0){
	  	            clearConfig();
	  	          sysConfigState1();
                    initState = 0;
	  	        }
				play(recorder);
                //leave state
				state = state0;
				initState = 1;
				clearLCD();
                                //enable_interrupts();
				break;
		} // Switch
  } // While
} // Main
  
  
  
  
  
  
