#include  "../header/api.h"    		// private library - API layer



//-------------------------------------------------------------
//           increment RGB L.E.D color value
//-------------------------------------------------------------

int incrementRgbLed(int RGB){
	RGB += 1; //TODO Check if good
    if (RGB>=0x8){
        RGB = 0;
    }
	updateRGB(RGB);

}
