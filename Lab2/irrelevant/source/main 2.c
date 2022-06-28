#include  "../header/api.h"    		// private library - API layer
#include  "../header/app.h"    		// private library - APP layer

enum FSMstate state;
enum SYSmode lpm_mode;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void main(void){
  
  state = state0;  // start in idle state on RESET
  lpm_mode = mode0;     // start in idle state on RESET
  sysConfig();
  
  while(1){
	switch(state){
	  case state0:
		printSWs2LEDs();
                enterLPM(lpm_mode);
		break;
		 
	  case state1:
		disable_interrupts();
		incLEDs(1);
		delay(LEDs_SHOW_RATE);	// delay of 62.5 [ms]
		enable_interrupts();
		break;
		 
	  case state2:
		disable_interrupts();
		incLEDs(-1);
		delay(LEDs_SHOW_RATE);		// delay of 62.5 [ms]
		enable_interrupts();
		break;
<<<<<<< HEAD
	  case state3: // buzzer ADC
		if (!initState){
            initState = 1;
		    configState3();	
	  	}
                 ADC10CTL0 |= ENC;
                TA1CCR1 = 0x0001;
		enterLPM(lpm_mode);
		//state3FrequencyIn =calcFrequency3(state3FrequencyIn);
		//state3FrequencyOut = (int)(BUZZER_FACTOR*state3FrequencyIn);
		//sing(state3FrequencyOut);
                
		break;

		case state4:
			if (!initState){
            initState = 1;
		    configState3();	
	  	}
                 ADC10CTL0 |= ENC;
                TA1CCR1 = 0x0001;
		enterLPM(lpm_mode);
		
                
		break;

=======
		
>>>>>>> d65fd191b344dff7b6d5022cfe36123d84261ea7
	}
  }
}
#pragma clang diagnostic pop
  
  
  
  
  
  