cmake_minimum_required(VERSION 3.21)
project(Lab2 C)

set(CMAKE_C_STANDARD 11)

include_directories(hanan/drive-download-20220427T163133Z-001/header)

add_executable(Lab2
        hanan/drive-download-20220427T163133Z-001/header/api.h
        hanan/drive-download-20220427T163133Z-001/header/app.h
        hanan/drive-download-20220427T163133Z-001/header/bsp.h
        hanan/drive-download-20220427T163133Z-001/header/halGPIO.h
        hanan/drive-download-20220427T163133Z-001/source/api.c
        hanan/drive-download-20220427T163133Z-001/source/bsp.c
        hanan/drive-download-20220427T163133Z-001/source/halGPIO.c
        hanan/drive-download-20220427T163133Z-001/source/main.c
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_01.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_02.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_03.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_04.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_05.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_06.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_07.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_08.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_09.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_10.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_11.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_12.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_13.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_14.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_16.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2x33_adc10_temp.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_01.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_02.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_03.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_04.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_05.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_06.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_07.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_08.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_10.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_11.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_13.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_14.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_16.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_17.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_19.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_20.c"
        "hanan/LAB2 Code Example MSP430G2xx3/msp430g2xx3_ta_21.c")
