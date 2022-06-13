#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

/* Follow This Link for Code flow Diagrams: 
*/


enum FSMstate state;
enum SYSmode lpm_mode;
int initState;// initState is 1 if state has changed
int timerDelayMs = 500; // defult

void main(void)
{
	initState = 1;
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
	  	        if (initState >0){
	  	            clearConfig();
	  	            sysConfigState1();
	  	            initState = 0;
	  	        }

				break;
		case state2:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;	
	  	case state3:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;
		case state4:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;
		case state5:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;
		case state6:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;
		case state7:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;
		case state8:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;
		case state9:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				break;					
		} // Switch
  } // While
} // Main
  
  
  
  
  
  
