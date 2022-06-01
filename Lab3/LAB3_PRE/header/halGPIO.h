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
static int menuIndex;
static int outNote;
extern void sysConfig(void);
extern void sysConfigState1(void);

extern void delay(unsigned int);
extern void enterLPM(unsigned char);
extern void playNote(int);
extern void enable_interrupts();
extern void disable_interrupts();
extern int recordNote();
extern int getSongChoice();
extern void showMenu();
extern void showInvalidChoiceMsg();
extern void playSong(int song[], int size);






extern __interrupt void PBs_handler(void);
extern __interrupt void timerA_ISR(void);
extern __interrupt void timerB_ISR(void);
extern __interrupt void DMA_ISR(void);
extern __interrupt void Keypad_handler(void);
#endif







/*

 0x254; // 1760
        break;
    case 0xA:
        TBCCR0 = 0x233; // 1864
        break;
    case 0xB:
        TBCCR0 = 0x212; // 1975
        break;
    case 0xC:
        TBCCR0 = 0x1F5; //
 case 0:
        TBCCR0 = 0x3EA; // 1046[Hz]
        break;
    case 1:
        TBCCR0 = 0x3B2; // 1108[Hz]
        break;
    case 2:
        TBCCR0 = 0x37D; // 1174
        break;
    case 3:
        TBCCR0 = 0x34B; // 1244
        break;
    case 4:
        TBCCR0 = 0x31C; // 1318
        break;
    case 5:
        TBCCR0 = 0x2EF; // 1397
        break;
    case 6:
        TBCCR0 = 0x2C4; // 1480
        break;
    case 7:
        TBCCR0 = 0x29D; // 1567
        break;
    case 8:
        TBCCR0 = 0x277; // 1661
        break;
    case 9:
        TBCCR0 = 0x254; // 1760
        break;
    case 0xA:
        TBCCR0 = 0x233; // 1864
        break;
    case 0xB:
        TBCCR0 = 0x212; // 1975
        break;
    case 0xC:
        TBCCR0 = 0x1F5; // 2093*/
