#ifndef _EXTERNAL_INTERRUPT_PRV_H
#define _EXTERNAL_INTERRUPT_PRV_H

#include "ExternalInterrupt.h"
#include <VL/MCU.h>

#define MCUCR_PTR ((volatile u8 *)0x55)
#define MCUCSR_PTR ((volatile u8 *)0x54)
#define GICR_PTR ((volatile u8 *)0x5b)

#define ISC00_PIN 0
#define ISC01_PIN 1
#define ISC10_PIN 2
#define ISC11_PIN 3
#define ISC2_PIN 6
#define INT0_PIN 6
#define INT1_PIN 7
#define INT2_PIN 5

#define INT0_ISR_VCT ISR_VECTOR(1)
#define INT1_ISR_VCT ISR_VECTOR(2)
#define INT2_ISR_VCT ISR_VECTOR(3)

ISR_DECL(INT0_ISR_VCT)
ISR_DECL(INT1_ISR_VCT)
ISR_DECL(INT2_ISR_VCT)

#endif