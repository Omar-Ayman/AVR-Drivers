#ifndef _PWM_PRV_H
#define _PWM_PRV_H

#include "PWM.h"

#include <VL/MCU.h>

typedef ENUM_PACKED Timer_WGM8bit {
    Timer_Normal            = 0b00,
    Timer_PhaseCorrectPWM   = 0b01,
    Timer_CTC               = 0b10,
    Timer_FastPWM           = 0b11,
} Timer_WGM8bit;

struct TIMSK_RegStruct {
    u8 TOIE0_pin : 1;
    u8 OCIE0_pin : 1;
    u8 TOIE1_pin : 1;
    u8 OCIE1B_pin : 1;
    u8 OCIE1A_pin : 1;
    u8 TICIE1_pin : 1;
    u8 TOIE2_pin : 1;
    u8 OCIE2_pin : 1;
};

struct TIFR_RegStruct {
    u8 TOV0_pin : 1;
    u8 OCF0_pin : 1;
    u8 TOV1_pin : 1;
    u8 OCF1B_pin : 1;
    u8 OCF1A_pin : 1;
    u8 ICF1_pin : 1;
    u8 TOV2_pin : 1;
    u8 OCF2_pin : 1;
};

struct TCCRx_RegStruct {
    u8 CSx_pins : 3;
    u8 WGMx1_pin : 1;
    u8 COMx_pins : 2;
    u8 WGMx0_pin : 1;
    u8 FOCx_pin : 1;
};

struct TCCRA1_RegStruct {
    u8 WGM1L_pins : 2;
    u8 FOC1B_pin : 1;
    u8 FOC1A_pin : 1;
    u8 COM1B_pins : 2;
    u8 COM1A_pins : 2;
};

struct TCCRB1_RegStruct {
    u8 CS1_pins : 3;
    u8 WGM1H_pins : 2;
    u8 _reserved : 1;
    u8 ICES1_pin : 1;
    u8 ICNC1_pin : 1;
};

#define TIMSK_ADR 0x59
#define TIMSK_RAW (*((volatile u8 *)TIMSK_ADR))
#define TIMSK_REG (*((volatile struct TIMSK_RegStruct *)TIMSK_ADR))
#define TIFR_REG (*((volatile struct TIFR_RegStruct *)0x58))

#define TCCR0_ADR 0x53
#define TCCR1A_ADR 0x4f
#define TCCR2_ADR 0x45

#define TCCR0_PTR    ((volatile struct TCCRx_RegStruct  *)TCCR0_ADR)
#define TCCR0_RAW    ((volatile u8 *)TCCR0_ADR)
#define TCCR2_PTR    ((volatile struct TCCRx_RegStruct  *)TCCR2_ADR)
#define TCCR2_RAW    ((volatile u8 *)TCCR2_ADR)
#define TCCR1A_REG (*((volatile struct TCCRA1_RegStruct *)TCCR1A_ADR))
#define TCCR1A_RAW (*((volatile u8 *)TCCR1A_ADR))
#define TCCR1B_REG (*((volatile struct TCCRB1_RegStruct *)0x4e))

#define TCNT0_PTR   ((volatile u8  *)0x52)
#define TCNT2_PTR   ((volatile u8  *)0x44)
#define TCNT1_REG (*((volatile u16 *)0x4c))

#define OCR0_PTR  ((volatile u8  *)0x5c)
#define OCR2_PTR  ((volatile u8  *)0x43)
#define OCR1A_PTR ((volatile u16 *)0x4a)
#define OCR1B_PTR ((volatile u16 *)0x48)

#define ICR1_REG (*((volatile u16 *)0x46))

#define TMR0_COMP_ISR_VCT ISR_VECTOR(10)
#define TMR0_OVFL_ISR_VCT ISR_VECTOR(11)
#define TMR2_COMP_ISR_VCT ISR_VECTOR(4)
#define TMR2_OVFL_ISR_VCT ISR_VECTOR(5)

#endif