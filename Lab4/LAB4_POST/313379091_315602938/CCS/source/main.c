/*
file description: C program for DCS lab4 - FSM with UART communication 
spec: https://github.com/cokfi/dcs-labs/tree/main/Lab4/spec
programmers: Kfir Cohen and Ron Tal 
MCU: MSP430
comments: Board connectivity is in the header file bsp.h
Menu:
	1. Blink RGB LED, color by color with delay of X[ms]
	2. Count up onto LCD screen with delay of X[ms]
	3. Count down onto LCD screen with delay of X[ms]
	4. Get delay time X[ms]:
	5. Potentiometer 3-digit value [v]
	6. Clear LCD screen
	7. Show menu
	8. Sleep

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
int timerDelayMs = 500; // X[ms] from Menu, 500 [ms] is the defult

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
	  	      //enable_interrupts();
				enterLPM(lpm_mode);
				RGB = incrementRgbLed(RGB);
				if (state != state1)
					initState = 1;
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
				enterLPM(lpm_mode); // sleep while hall uart ISR is getting the Delay
				if (isDelaySet){ // if stringDelay is set at hall
				    timerDelayMs = setDelay();
				    state = state0;
				    isDelaySet = 0;
				}
				if (state != state4)
					initState = 1;
				break;
		case state5:
//	  	        if (initState >0){
//	  	            clearConfig();
//	  	          	sysConfigState2();
//                    initState = 0;
//	  	        }
		        state = state0;
				break;
		case state6:
	  	        clearConfig();
				//clearLCD();
				state = state0;
				break;
		case state7: // pc has printed menu
                if (initState >0){
                    clearConfig();
                    sysConfigState7();
                    initState = 0;
                }
                enterLPM(lpm_mode);
//                if (CCR0 ==0xfc){
//                  CCR0 =0x7E;
//                }
//                else {
//                    CCR0 = 0xfc;
//                }
                state = state0;
				break;
		case state8: // go to sleep
				clearConfig();		
				state = state0;
				break;
						
		} // Switch
  } // While
} // Main
  
  
  
  
  
  
