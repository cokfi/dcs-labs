///*
// * FLASH.c
// *
// *  Created on: 13 Aug 2022
// *      Author: rontal
// */
//#include <msp430.h>
///* This is the IAR compiler */
//
//struct FileMemory
//{
//    int file_count = 0;
//    int filename_list[200];
//    unsigned int file_pointers_list[200];
//    int file_size_listp[200];
//}
//void flash_init()
//{
//    /* Flash timing generator frequency: ideally around 366 Hz
//     *  257 Hz < Fftg < 476 Hz from (datasheet slas504 p55) */
//    switch (get_mclk_freq_mhz())
//    {
//    case 1:
//        FCTL2 = FWKEY | FSSEL_2 | FN1 | FN0; /* Fftg = MCLK/3 = 333 */
//        break;
//    case 8:
//        FCTL2 = FWKEY | FSSEL_2 | FN4 | FN2 | FN1; /* Fftg = MCLK/22 = 364 */
//        break;
//    case 12:
//        FCTL2 = FWKEY | FSSEL_2 | FN5 | FN0; /* Fftg = MCLK/33 = 364 */
//        break;
//    case 16:
//        FCTL2 = FWKEY | FSSEL_2 | FN5 | FN3 | FN2; /* Fftg = MCLK/44 = 364 */
//        break;
//    }
//}
//
///* programs 1 byte (8 bit) into the flash memory,
// * returns non 0 if the write failed, that is when a segment erase
// * is needed because the data_ptr location was previously written */
//int flash_write_byte(unsigned char *data_ptr, unsigned char byte)
//{
//    if (*data_ptr == byte)
//    {
//        return 0;
//    }
//    else if (*data_ptr != 0xFF)
//    {
//        /* don't allow 2 several consecutive writes on the same location */
//        return -1;
//    }
//
//    flash_init();
//    /* interrupts are automatically disabled during
//     * flash operation as EEI = 0 and EEIEX = 0 (FCTL1 bits) */
//    FCTL3 = FWKEY; /* Lock = 0 */
//    FCTL1 = FWKEY | WRT; /* WRT = 1 */
//    *data_ptr = byte; /* program Flash byte */
//    FCTL1 = FWKEY; /* WRT = 0 */
//    FCTL3 = FWKEY | LOCK; /* Lock = 1 */
//
//    return 0;
//}
//
///* programs 1 word (16 bit) into the flash memory,
// * returns non 0 if the write failed, that is when a segment erase
// * is needed because the data_ptr location was previously written */
//int flash_write_word(unsigned int *data_ptr, unsigned int word)
//{
//    if (*data_ptr == word)
//    {
//        return 0;
//    }
//    else if (*data_ptr != 0xFFFF)
//    {
//        /* don't allow 2 several consecutive writes on the same location */
//        return -1;
//    }
//
//    flash_init();
//
//    FCTL3 = FWKEY; /* Lock = 0 */
//    FCTL1 = FWKEY | WRT; /* WRT = 1 */
//    *data_ptr = word; /* program Flash word */
//    FCTL1 = FWKEY; /* WRT = 0 */
//    FCTL3 = FWKEY | LOCK; /* Lock = 1 */
//
//    return 0;
//}
//
///* erases 1 Segment of flash memory */
//void flash_erase_segment(unsigned int *data_ptr)
//{
//    flash_init();
//    FCTL3 = FWKEY; /* Lock = 0 */
//    FCTL1 = FWKEY | ERASE; /* ERASE = 1 */
//    *data_ptr = 0; /* erase Flash segment */
//    FCTL1 = FWKEY; /* ERASE = 0 */
//    FCTL3 = FWKEY | LOCK; /* Lock = 1 */
//}
//
//void flash_erase_info_memory()
//{
//    flash_erase_segment((unsigned int*) INFOD_START);
//    flash_erase_segment((unsigned int*) INFOC_START);
//    flash_erase_segment((unsigned int*) INFOB_START);
//    /* INFOA contains calibration data and is protected by LOCKA */
//}

// 8-bit value to write to segment A
#include "../../header/FLASH/FLASH.h"

flash_configured_flag = 0;
static struct FileMemory mem;

void configureFlash()
{
    if (CALBC1_1MHZ == 0xFF)               // If calibration constant erased
    {
        while (1)
            ;                               // do not load, trap CPU!!
    }

    DCOCTL = 0;                          // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                          // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;
    FCTL2 = FWKEY + FSSEL0 + FN1;           // MCLK/3 for Flash Timing Generator
    flash_configured_flag = 1;
}

void writeToFlash(char val)
{
    if (!flash_configured_flag)
        configureFlash();

}

//int main(void)
//{
//    if (CALBC1_1MHZ == 0xFF)                   // If calibration constant erased
//    {
//        while (1)
//            ;                               // do not load, trap CPU!!
//    }
//
//    DCOCTL = 0;                          // Select lowest DCOx and MODx settings
//    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
//    DCOCTL = CALDCO_1MHZ;
//    FCTL2 = FWKEY + FSSEL0 + FN1;           // MCLK/3 for Flash Timing Generator
//    value = 0;                                // initialize value
//
//    while (1)                                  // Repeat forever
//    {
//        write_SegC(value++);                 // Write segment C, increment value
//        copy_C2D();                             // Copy segment C to D
//        __no_operation();                       // SET BREAKPOINT HERE
//    }
//}

void write_SegC(char value)
{
    char *Flash_ptr;                          // Flash pointer
    unsigned int i;

    Flash_ptr = (char*) 0x1040;              // Initialize Flash pointer
    FCTL1 = FWKEY + ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                            // Clear Lock bit
    *Flash_ptr = 0;                        // Dummy write to erase Flash segment

    FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

    for (i = 0; i < 64; i++)
    {
        *Flash_ptr++ = value;                   // Write value to flash
    }

    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void copy_C2D(void)
{
    char *Flash_ptrC;                         // Segment C pointer
    char *Flash_ptrD;                         // Segment D pointer
    unsigned int i;

    Flash_ptrC = (char*) 0x1040;           // Initialize Flash segment C pointer
    Flash_ptrD = (char*) 0x1000;           // Initialize Flash segment D pointer
    FCTL1 = FWKEY + ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                            // Clear Lock bit
    *Flash_ptrD = 0;                     // Dummy write to erase Flash segment D
    FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

    for (i = 0; i < 64; i++)
    {
        *Flash_ptrD++ = *Flash_ptrC++;      // copy value segment C to segment D
    }

    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}
