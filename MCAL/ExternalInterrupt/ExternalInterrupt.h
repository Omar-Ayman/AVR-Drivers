
#ifndef _EXTERNAL_INTERRUPT_H
#define _EXTERNAL_INTERRUPT_H

#include <VL/MCU.h>
#include <MCAL/DIO/DIO.h>

#define INT0_PIN_INFO {PORTD_IDX, PIN2_IDX}
#define INT1_PIN_INFO {PORTD_IDX, PIN3_IDX}
#define INT2_PIN_INFO {PORTB_IDX, PIN2_IDX}

typedef ENUM_PACKED ExternalInterrupt_Type {
    ExternalInterrupt_onLowLevel = 0b00,
    ExternalInterrupt_onChange = 0b01,
    ExternalInterrupt_onFallingEdge = 0b10,
    ExternalInterrupt_onRisingEdge = 0b11
} ExternalInterrupt_Type;

typedef void (*ExternalInterruptHandle)(void);

void ExternalInterrupt_setupPin(PinInfo pin, ExternalInterrupt_Type type, ExternalInterruptHandle handle);

#endif
