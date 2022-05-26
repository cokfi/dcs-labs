#ifndef _halGPIO_H_
#define _halGPIO_H_

#define SONG1_SIZE 54
#define SONG2_SIZE 47
#define SONG3_SIZE 40
#define RECORD_SIZE 32

#include  "../header/bsp.h"    		// private library - BSP layer
#include  "../header/app.h"    		// private library - APP layer
#include "../header/LCD.h"

extern enum FSMstate state;   // global variable
extern enum SYSmode lpm_mode; // global variable
extern char keypadButton;
static int menuIndex;
static unsigned int outNote;
extern void sysConfig(void);

extern void delay(unsigned int);
extern void enterLPM(unsigned char);
extern void playNote(char);
extern void enable_interrupts();
extern void disable_interrupts();
extern char recordNote();
extern int getSongChoice();
extern void showMenu();
extern void showInvalidChoiceMsg();
extern void playSong(int song[], int size);

extern int song1[];
extern int song2[];
extern int song3[];

extern __interrupt void PBs_handler(void);
extern __interrupt void timerA_ISR(void);
extern __interrupt void timerB_ISR(void);
extern __interrupt void DMA_ISR(void);
extern __interrupt void Keypad_handler(void);
#endif







