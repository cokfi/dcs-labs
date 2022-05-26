#ifndef _halGPIO_H_
#define _halGPIO_H_

#include  "../header/bsp.h"    		// private library - BSP layer
#include  "../header/app.h"    		// private library - APP layer

<<<<<<< HEAD
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
#define TOL 					1
=======

extern enum FSMstate state;   // global variable
extern enum SYSmode lpm_mode; // global variable
>>>>>>> d65fd191b344dff7b6d5022cfe36123d84261ea7

extern void sysConfig(void);
extern void print2LEDs(unsigned char);
extern void clrLEDs(void);
extern void toggleLEDs(char);
extern void setLEDs(char);
extern unsigned char readSWs(void);
extern void delay(unsigned int);
extern void enterLPM(unsigned char);
extern void incLEDs(char);
extern void enable_interrupts();
extern void disable_interrupts();

extern __interrupt void PBs_handler(void);

#endif







