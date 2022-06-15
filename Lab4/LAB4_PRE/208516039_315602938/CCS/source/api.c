#include  "../header/api.h"    		// private library - API layer


const unsigned int powerTable [] = {1,10,100,1000,10000,100000,1000000};
//-------------------------------------------------------------
//           increment RGB L.E.D color value
//-------------------------------------------------------------

int incrementRgbLed(int RGB){
    updateRGB(RGB);
	RGB += 1;
    if (RGB>=0x8){
        RGB = 0;
    }
    return RGB;
	

}
int setDelay(){
    int Delay = 0;
    int k;
    for(k=0; k<delayLength; k++){
        Delay += (((int)stringDelay[k])-48)*powerTable[delayLength-k-1];
    }
    return Delay;
}
