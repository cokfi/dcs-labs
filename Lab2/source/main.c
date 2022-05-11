#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

int initState = 0; // active low
void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  int isSecPassed=0;//active ==10
  int elapsed_counter = 60; //secs
  int state3FrequencyIn =10; // Hz
  int state3FrequencyOut; // Hz
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
		displayFin();
		break;
		 
	  case state2: // 1 minute time elapsed
	  	if (!initState){
            initState = 1;
		    configState2();
	  	}
		enterLPM(lpm_mode);
		if(isSecPassed>=SEC_SCALE && elapsed_counter>0){
			elapsed_counter--;
			displayTimeElapsed(elapsed_counter);
			isSecPassed=0;
		}
		else if (elapsed_counter>=0){
			isSecPassed++;
			}
		else{
			state = state0;
		}	
		break;
	case state3: // buzzer ADC
		if (!initState){
            initState = 1;
		    configState3();	
	  	}
		enterLPM(lpm_mode);
		state3FrequencyIn =calcFrequency3(state3FrequencyIn);
		state3FrequencyOut = (int)(BUZZER_FACTOR*state3FrequencyIn);
		sing(state3FrequencyOut);
		break;
		 
	  case state1:
	 	
		break;	
	}
  }
}
  
  
  
  
  
  