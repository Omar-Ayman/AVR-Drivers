#ifndef _ADC_PRV_H
#define _ADC_PRV_H

#include "ADC.h"

struct ADCSRA_RegStruct {
    u8 ADPS : 3;
    u8 ADIE_pin : 1;
    u8 ADIF_pin : 1;
    u8 ADATE_pin : 1;
    u8 ADSC_pin : 1;
    u8 ADEN_pin : 1;
};

struct ADMUX_RegStruct {
    u8 MUX : 5;
    u8 ADLAR_pin : 1;
    u8 REFS : 2;
};

// struct TCCR0_RegStruct {
//     u8 CS0: 3;
//     u8 WGM01_pin: 1;
//     u8 COM0: 2;
//     u8 WGM00_pin: 1;
//     u8 FOC0_pin: 1;
// };

// struct TCCR1A_RegStruct {
//     u8 WGM1L: 2;
//     u8 FOC1A_pin: 1;
//     u8 FOC1B_pin: 1;
//     u8 COM1B: 2;
//     u8 COM1A: 2;
// };

// struct TCCR1B_RegStruct {
//     u8 CS1: 3;
//     u8 WGM1H: 2;
//     u8 _reserved: 1;
//     u8 ICES1_pin: 1;
//     u8 ICNC1_pin: 1;
// };

#define ADCSRA_REG (*((volatile struct ADCSRA_RegStruct*) 0x26))
#define ADMUX_REG (*((volatile struct ADMUX_RegStruct*) 0x27))
#define ADC_REG (*((volatile u16 *) 0x24))
// #define TCCR0_REG (*((volatile struct TCCR0_RegStruct*) 0x53))
// #define TCCR1A_REG (*((volatile struct TCCR1A_RegStruct*) 0x4f))
// #define TCCR1B_REG (*((volatile struct TCCR1B_RegStruct*) 0x4e))

void ADC_initGeneral();

#endif