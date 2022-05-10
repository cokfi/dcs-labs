#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;
bool initState = true;

void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  char countDownStr;
  sysConfig();
  
  while(1){
	switch(state){
	  case state0: // frquency counter
		enterLPM(lpm_mode);
		break;
		 
	  case state1:
	  	if (initState){
			configState1();
			displayFin();
		  }
		displayFin();
		break;
		 
	  case state2:
		disable_interrupts();
		incLEDs(-1);
		delay(LEDs_SHOW_RATE);		// delay of 62.5 [ms]
		enable_interrupts();
		break;
		
	}
  }
}
  
  
  
  
  
  