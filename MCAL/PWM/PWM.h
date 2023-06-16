#ifndef _PWM_H
#define _PWM_H

#include <MCAL/DIO/DIO.h>

#define OC0_PIN_INFO   {PORTB_IDX, PIN3_IDX}
#define OC1A_PIN_INFO  {PORTD_IDX, PIN5_IDX}
#define OC1B_PIN_INFO  {PORTD_IDX, PIN4_IDX}
#define OC2_PIN_INFO   {PORTD_IDX, PIN7_IDX}

#define PWM_MAX_MV 5000
#define PWM_MAX_DUTY_CYCLE ((u16)0xff)

typedef ENUM_PACKED OC0_WaveGenerationMode {
    OC0_NoClock             = 0b000,
    OC0_Prescale1           = 0b001,
    OC0_Prescale8           = 0b010,
    OC0_Prescale64          = 0b011,
    OC0_Prescale256         = 0b100,
    OC0_Prescale1024        = 0b101,
    OC0_ExtClkFallingEdge   = 0b110,
    OC0_ExtClkRisingEdge    = 0b111,
} OC0_WaveGenerationMode;

typedef u8 PWMCustomHandle;

void PWM_initDefault(PinInfo pin);

void PWM_initCustomFreq(PinInfo pin, u32 fr);

void PWM_writeDutyCycle(PinInfo pin, u16 dutyCycle);

void PWM_writeVolts(PinInfo pin, u16 milliVolt);

PWMCustomHandle PWMCustom_init(PinInfo pin, u32 fr);

void PWMCustom_writeDutyCycle(PWMCustomHandle handle, u8 dutyCycle);

void PWMCustom_writeVolts(PWMCustomHandle handle, u16 milliVolt);

#endif