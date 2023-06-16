#ifndef _UART_PRV_H
#define _UART_PRV_H

#include "UART.h"

#include <VL/MCU.h>

#define UDR_REG (*((volatile u8 *)0x2c))

struct UCSRA_RegStruct {
    u8 MPCM_pin : 1;
    u8 U2X_pin : 1;
    u8 PE_pin : 1;
    u8 DOR_pin : 1;
    u8 FE_pin : 1;
    u8 UDER_pin : 1;
    u8 TXC_pin : 1;
    u8 RXC_pin : 1;
};
#define UCSRA_REG (*((volatile struct UCSRA_RegStruct *)0x2b))

struct UCSRB_RegStruct {
    u8 aXB8_pins : 2;
    u8 UCSZ2_pin : 1;
    u8 aXEN_pins : 2;
    u8 UDRIE_pin : 1;
    u8 aXCIE_pins : 2;
};
#define UCSRB_REG (*((volatile struct UCSRB_RegStruct *)0x2a))

struct UCSRC_RegStruct {
    u8 UCPOL_pin : 1;
    u8 UCSZ_pins : 2;
    u8 USBS_pin : 1;
    u8 UPM_pins : 2;
    u8 UMSEL_pin : 1;
    u8 URSEL_pin : 1;
};
#define UCSRC_REG (*((volatile struct UCSRC_RegStruct *)0x40))

struct UBRRH_RegStruct {
    u8 UBRRH_pins : 4;
    u8 _reserved : 3;
    u8 URSEL_pin : 1;
};
#define UBRRH_REG (*((volatile struct UBRRH_RegStruct *)0x40))

#define UBRRL_REG (*((volatile u8 *)0x29))

typedef ENUM_PACKED URSEL_Enum {
    URSEL_UBRRH = 0,
    URSEL_UCSRC = 1
} URSEL_Enum;

#define UART_RXC_ISR_VCT ISR_VECTOR(13)

void UART_setBaudRate(u32 baudRate);

u8 UART_dequeueBufferAtomic();
u8 UART_consumeBufferAwait();
u8 UART_consumeBuffer(u8 *dataPtr);

#endif