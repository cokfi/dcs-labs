#ifndef _halGPIO_H_
#define _halGPIO_H_

#define SONG1_SIZE 54
#define SONG2_SIZE 47
#define SONG3_SIZE 40
#define RECORD_SIZE 32

#include  "../header/bsp.h"    		// private library - BSP layer
#include  "../header/app.h"    		// private library - APP layer
//#include "../header/LCD.h"

extern enum FSMstate state;   // global variable
extern enum SYSmode lpm_mode; // global variable
static int menuIndex;
static int outNote;
extern char volatge[3];
extern char stringDelay[16];
extern  int isDelaySet;
extern  int delayLength;

/*----------------------------------------------------------
  LCD CONFIG: change values according to your port pin selection
------------------------------------------------------------*/
// #define CHECKBUSY	1  // using this define, only if we want to read from LCD

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT DelayMs(5)
#endif
#define LCD_EN(a)	(!a ? (P2OUT&=~0X20) : (P2OUT|=0X20)) // P2.5 is lcd enable pin
#define LCD_EN_DIR(a)	(!a ? (P2DIR&=~0X20) : (P2DIR|=0X20)) // P2.5 pin direction 

#define LCD_RS(a)	(!a ? (P2OUT&=~0X40) : (P2OUT|=0X40)) // P2.6 is lcd RS pin
#define LCD_RS_DIR(a)	(!a ? (P2DIR&=~0X40) : (P2DIR|=0X40)) // P2.6 pin direction  
  
#define LCD_RW(a)	(!a ? (P2OUT&=~0X80) : (P2OUT|=0X80)) // P2.7 is lcd RW pin
#define LCD_RW_DIR(a)	(!a ? (P2DIR&=~0X80) : (P2DIR|=0X80)) // P2.7 pin direction

#define LCD_DATA_OFFSET 0x04 //data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset
   
#define LCD_DATA_WRITE	P1OUT
#define LCD_DATA_DIR	P1DIR
#define LCD_DATA_READ	P1IN
/*---------------------------------------------------------
  END CONFIG
-----------------------------------------------------------*/
#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1
#define LCD_MODE        FOURBIT_MODE
#define SMCLK_FREQUENCY 0x100000
   
#define OUTPUT_PIN      1	
#define INPUT_PIN       0	
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x00	

#define LCD_STROBE_READ(value)	LCD_EN(1), \
				asm("nop"), asm("nop"), \
				value=LCD_DATA_READ, \
				LCD_EN(0) 

#define	lcd_cursor(x)		lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()		lcd_cmd(0x01)
#define lcd_putchar(x)		lcd_data(x)
#define lcd_goto(x)		lcd_cmd(0x80+(x))
#define lcd_cursor_right()	lcd_cmd(0x14)
#define lcd_cursor_left()	lcd_cmd(0x10)
#define lcd_display_shift()	lcd_cmd(0x1C)
#define lcd_home()		lcd_cmd(0x02)
#define cursor_off              lcd_cmd(0x0C)
#define cursor_on               lcd_cmd(0x0F) 
#define lcd_function_set        lcd_cmd(0x3C) // 8bit,two lines,5x10 dots 
#define lcd_new_line            lcd_cmd(0xC0)
extern void sysConfig(void);
extern void sysConfigState1(void);
extern void sysConfigState2(void);
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

//LCD
extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char);
extern void lcd_puts(const char * s);
extern void lcd_init(void);
extern void lcd_strobe(void);
extern void DelayMs(unsigned int);
extern void DelayUs(unsigned int);




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
