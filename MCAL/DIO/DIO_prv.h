
#ifndef DIO_PRV_H
#define DIO_PRV_H

#include <VL/Types.h>

#define PORTA_PTR ((volatile u8 *)(0x3B))
#define DDRA_PTR ((volatile u8 *)(0x3A))
#define PINA_PTR ((volatile u8 *)(0x39))

#define PORTB_PTR ((volatile u8 *)(0x38))
#define DDRB_PTR ((volatile u8 *)(0x37))
#define PINB_PTR ((volatile u8 *)(0x36))

#define PORTC_PTR ((volatile u8 *)(0x35))
#define DDRC_PTR ((volatile u8 *)(0x34))
#define PINC_PTR ((volatile u8 *)(0x33))

#define PORTD_PTR ((volatile u8 *)(0x32))
#define DDRD_PTR ((volatile u8 *)(0x31))
#define PIND_PTR ((volatile u8 *)(0x30))

#endif
