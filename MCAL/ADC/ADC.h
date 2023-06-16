#ifndef _ADC_H
#define _ADC_H

#include <MCAL/DIO/DIO.h>

#define ADC_MAX_VALUE 1023

#define ADC_MAX_MV 4995

typedef ENUM_PACKED ADC_PrescalerSelect {
    ADC_Prescale2   = 0b000,
    ADC_Prescale4   = 0b010,
    ADC_Prescale8   = 0b011,
    ADC_Prescale16  = 0b100,
    ADC_Prescale32  = 0b101,
    ADC_Prescale64  = 0b110,
    ADC_Prescale128 = 0b111
} ADC_PrescalerSelect;

typedef ENUM_PACKED ADC_ReferenceSelect {
    ADC_ReferenceAREF  = 0b00,
    ADC_ReferenceAVCC  = 0b01,
    ADC_Reference2_56V = 0b11
} ADC_ReferenceSelect;

void ADC_init(PinInfo pin);

u16 ADC_readValue(PinInfo pin);

u16 ADC_readMilliVolts(PinInfo pin);

#endif