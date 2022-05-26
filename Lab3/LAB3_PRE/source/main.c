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
char keypadButton;
const int song1[SONG1_SIZE] ={2,7,7,7,2,4,4,2,11,11,9,9,7,2,7,7,7,2,4,4,2,11,11,9,9,7,2,7,7,7,2,7,7,7,7,7,7,2,7,7,7,2,7,7,7,2,4,4,2,11,11,9,9,7}; // Uncle Moshe
const int song2[SONG2_SIZE] ={0, 5,9,0,5,9,9, 7,7,7,7,9, 10,10,10,12,10,9,7, 9,9,9,9,5,7,9, 10,10,10,12,10,10, 9,5,9,12,12, 0,4,7,10,9,7, 5,5,5,5}; // Our Auto
const int song3[SONG3_SIZE] ={4,7,4,4,7,4,12,11,9,7,5,2,5,9,7,7,5,4,2,0,4,7,4,4,7,4,12,11,9,7,5,2,5,9,7,7,5,4,2,0}; // Hands Up!



void main(void)
{
	static int recorder[RECORD_SIZE];
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
				disable_interrupts();
				record(recorder);
				enable_interrupts();
				break;
	  	case state2:
				disable_interrupts();
				play();
				enable_interrupts();
				break;
		} // Switch
  } // While
} // Main
  
  
  
  
  
  
