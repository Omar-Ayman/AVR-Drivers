/***************************************************************************************/
/****************************  IMT School Training Center ******************************/
/***************************************************************************************/
/** This file is developed by IMT School training center, All copyrights are reserved **/
/***************************************************************************************/
#ifndef _MCU_CONFIG
#define _MCU_CONFIG

#ifndef __AVR_ATmega32__
#define __AVR_ATmega32__
#endif

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <VL/Types.h>

// #include <avr/io.h>
#include <util/delay.h>

#define ISR_VECTOR(IDX) __vector_ ## IDX
#define ISR_HEAD(VCT) void VCT (void)
#define ISR_DECL(VCT) ISR_HEAD(VCT) __attribute__ ((signal));
#define ISR_HNDL(VCT) ISR_DECL(VCT) ISR_HEAD(VCT)

// register structs

struct SREG_RegStruct {
    u8 C_pin : 1;
    u8 Z_pin : 1;
    u8 N_pin : 1;
    u8 V_pin : 1;
    u8 S_pin : 1;
    u8 H_pin : 1;
    u8 T_pin : 1;
    u8 I_pin : 1;
};

// general registers

#define SREG_REG (*((volatile struct SREG_RegStruct *)0x5f))

#endif