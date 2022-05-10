#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

int initState = 0; // active low
void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  
  while(1){
	switch(state){
	  case state0: // frquency counter
		enterLPM(lpm_mode);
		break;
		 
	  case state1:
	 	if (!initState){
            initState = 1;
		    configState1();
			
	  }
		enterLPM(lpm_mode);
	//	calculateFin();
		displayFin();
		break;
		 
	  case state2:
		
		break;
		
	}
  }
}
  
  
  
  
  
  