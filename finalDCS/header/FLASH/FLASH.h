/*
 * FLASH.h
 *
 *  Created on: 13 Aug 2022
 *      Author: rontal
 */

#ifndef HEADER_FLASH_FLASH_H_
#define HEADER_FLASH_FLASH_H_

#include <msp430.h>

struct FileMemory
{
    int file_count;
    int file_name_pointers[3];
    int file_start_pointers[3];
    int file_sizes[3];
};
char value;
static int flash_configured_flag;
void write_SegC(char value);
void copy_C2D(void);
void configureFlash();
#endif /* HEADER_FLASH_FLASH_H_ */
