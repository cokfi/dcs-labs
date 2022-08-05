#include  <msp430g2553.h>          // MSP430x2xx

//---------------register control ADC10CTL0-----------

typedef enum SelectReference{
    vref0 = SREF_0,  // 000 VR+ = VCC and VR− = VSS
    vref1 = SREF_1 , // 001 VR+ = VREF+ and VR− = VSS
    vref2 = SREF_2 , // 010 VR+ = VeREF+ and VR− = VSS
    vref3 = SREF_3 , // 011 VR+ = Buffered VeREF+ and VR− = VSS
    vref4 = SREF_4 , // 100 VR+ = VCC and VR− = VREF−/ VeREF−
    vref5 = SREF_5 , // 101 VR+ = VREF+ and VR− = VREF−/ VeREF−
    vref6 = SREF_6 , // 110 VR+ = VeREF+ and VR− = VREF−/ VeREF−
    vref7 = SREF_7   // 111 VR+ = Buffered VeREF+ and VR− = VREF−/ VeREF−
}SelectReference; // first word is VR+ second word is VR-

typedef enum SampleAndHoldTime{
    fourClks = ADC10SHT_0,         // 00 4 x ADC10CLKs
    eightClks = ADC10SHT_1,        // 01 8 x ADC10CLKs
    sixteenClks = ADC10SHT_2,      // 10 16 x ADC10CLKs
    sixtyfourClks = ADC10SHT_3     // 11 64 x ADC10CLKs   
}SampleAndHoldTime;
typedef enum SamplingRate{
    fast = 0x00,       // 0 Reference buffer supports up to ~200 ksps
    slow = adc10sr     // 1 Reference buffer supports up to ~50 ksps
}SamplingRate;
typedef enum ReferenceOutput{
    off = 0x00, // 0 Reference output off
    on =  REFOUT// 1 Reference output on
}ReferenceOutput;
typedef enum ReferenceBurst{
    continuously = 0x00, // 0 Reference buffer on continuously
    piecewise =  REFBURST// 1 Reference buffer on only during sample-and-conversion
}ReferenceBurst;
typedef enum MultiSampleAndConversion{
    risingEdge = 0x00,  //  0 The sampling requires a rising edge of the SHI signal to trigger each sample-and-conversion.
    automatic =  MSC    /*  1 The first rising edge of the SHI signal triggers the sampling timer,
                              but further sample-and-conversions are performed automatically as soon as the prior conversion is completed*/
}MultiSampleAndConversion;
typedef enum RefGeneratorVoltage{
    onePointFive = 0x00, //  0  1.5 V
    twoPointFive = REF2_5V// 1  2.5 V
}RefGeneratorVoltage;

//---------------register control ADC10CTL1-----------

typedef enum InputChannel{
    A0=INC_0,   //pin P1.0
    A1=INC_1,   //pin P1.1
    A2=INC_2,   //pin P1.2
    A3=INC_3    //pin P1.3
}InputChannel;
typedef enum ConversionSequenceMode{
    single = CONSEQ_0,          // 00 Single-channel-single-conversion
    sequence = CONSEQ_1,        //01 Sequence-of-channels 
    repeatSingle = CONSEQ_2,    //10 Repeat-single-channel
    repearSequence = CONSEQ_3   //11 Repeat-sequence-of-channels
}ConversionSequenceMode;

// TODO: check if more enums are needed for this register









