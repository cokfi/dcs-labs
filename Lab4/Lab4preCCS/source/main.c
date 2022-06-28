/*
file description: C program for DCS lab4 - FSM with UART communication 
spec: https://github.com/cokfi/dcs-labs/tree/main/Lab4/spec
programmer: Kfir Cohen
MCU: MSP430
Date: 13/06/22
*/


#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer


//-------------------------------------------------------------
//           global variables
//-------------------------------------------------------------
enum FSMstate state;
enum SYSmode lpm_mode;
int initState;// initState is 1 if state has changed
int timerDelayMs = 500; // defult

//-------------------------------------------------------------
//           main
//-------------------------------------------------------------
void main(void)
{
	initState = 1;
	state = state0;				// start in idle state on RESET
	lpm_mode = mode0;     // start in idle state on RESET
	int RGB = 0; // RGB L.E.D values are between 0 to 7
	sysConfig();
  while(1)
	{
		switch(state)
		{
	  	case state0:
    		enterLPM(lpm_mode);
			break;
	  	case state1: // blink RGB colors L.E.D
	  	        if (initState >0){
	  	            clearConfig();
	  	            sysConfigState1();
	  	            initState = 0;
					RGB = 0;
	  	        }
				enterLPM(lpm_mode);
				RGB = incrementRgbLed(RGB);
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
		case state4:// get timerDelayMs from PC (UART)
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState2();
                    initState = 0;
	  	        }
				getDelayTime();
				break;
		case state5:
	  	        if (initState >0){
	  	            clearConfig();
	  	          	sysConfigState5();
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
			state = state0;
				break;
						
		} // Switch
  } // While
} // Main
  
  
  
  
  
  
