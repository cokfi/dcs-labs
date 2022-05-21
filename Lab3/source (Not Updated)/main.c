#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

#define SONG1_SIZE 32
#define SONG2_SIZE 32
#define SONG3_SIZE 32
#define RECORD_SIZE 32  


enum FSMstate state;
enum SYSmode lpm_mode;

char keypadButton;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void main(void){
	static const int song1[SONG1_SIZE];
	static const int song2[SONG2_SIZE];
	static const int song3[SONG3_SIZE];

	static recorder[RECORD_SIZE];

	state = state0;				// start in idle state on RESET
	lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  
  while(1){
		switch(state){
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
#pragma clang diagnostic pop
  
  
  
  
  
  