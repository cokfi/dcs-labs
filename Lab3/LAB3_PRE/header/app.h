#ifndef _app_H_
#define _app_H_


enum FSMstate{state0,state1,state2,state3,state4}; // global variable
enum SYSmode{mode0,mode1,mode2,mode3,mode4}; // global variable
extern int song1[SONG1_SIZE];
extern int song2[SONG2_SIZE];
extern int song3[SONG3_SIZE];
extern int recorder[RECORD_SIZE];
extern int RGBmatrix[8];
extern unsigned int countingIndexRecord;
extern int keypadButton;
#endif







