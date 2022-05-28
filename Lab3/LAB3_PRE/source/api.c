#include  "../header/api.h"    		// private library - API layer


//-------------------------------------------------------------
//            Record Notes From KeyPad
//-------------------------------------------------------------

void record(int recorder[])
{
        clearLCD();
	//recordConfig();
	unsigned int i = 32;
	while(i){
                int newNote = recordNote(); 
                
                if(newNote == -1)
                {
                  continue;
                }
                playNote(newNote);
		recorder[32-i] = newNote;
                
                i--;
                //playNote(recorder[32-i]);
                
	}
}

//-------------------------------------------------------------
//            Play Songs
//-------------------------------------------------------------

void play(int recorder[]){
	int choice = getSongChoice();

	switch (choice)
	{
	case 1:
		playSong(song1, SONG1_SIZE);
		break;
	case 2:
		playSong(song2, SONG2_SIZE);
		break;
	case 3:
		playSong(song3, SONG3_SIZE);
		break;
	case 4:	
                playSong(recorder,RECORD_SIZE);
	default:
		break;
	}
}
