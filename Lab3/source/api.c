#include  "../header/api.h"    		// private library - API layer
#include  "../header/halGPIO.h"     // private library - HAL layer

//-------------------------------------------------------------
//            Record Notes From KeyPad
//-------------------------------------------------------------

void record(char* recorder){
	recordConfig();

	for (int i = 0; i < 32; i++)
	{
		recorder[i] = recordNote();
		playNote(recorder[i]);
	}
}

//-------------------------------------------------------------
//            Play Songs
//-------------------------------------------------------------

void play(){
	int choice = getSongChoice();

	switch (choice)
	{
	case 1:
		playSong(song1, SONG1_SIZE);
		break;
	case /* constant-expression */:
		playSong(song2, SONG2_SIZE);
		break;
	case /* constant-expression */:
		playSong(song3, SONG3_SIZE);
		break;
		
	default:
		break;
	}
}