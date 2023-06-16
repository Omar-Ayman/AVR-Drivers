
#include "DIO.h"
#include "DIO_prv.h"

#include <VL/BitArithmetics.h>

/* Define Array of pointers to hold all registers */
static volatile u8* DIO_OutRegisters [4] = {PORTA_PTR, PORTB_PTR, PORTC_PTR, PORTD_PTR};
static volatile u8* DIO_InRegisters  [4] = {PINA_PTR , PINB_PTR , PINC_PTR , PIND_PTR };
static volatile u8* DIO_DirRegisters [4] = {DDRA_PTR , DDRB_PTR , DDRC_PTR , DDRD_PTR };

void DIO_setPinDirection(PinInfo pin, u8 dir) {
	DIO_setPinDirectionInitVal(pin, dir, !dir);
}

void DIO_setPinDirectionInitVal(PinInfo pin, u8 dir, u8 val) {
	if (dir)
		SET_BIT(*DIO_DirRegisters[pin.port], pin.pin);
	else
		CLR_BIT(*DIO_DirRegisters[pin.port], pin.pin);

	DIO_writePin(pin, val);
}

u8 DIO_readPin(PinInfo pin) {
	return GET_BIT(*DIO_InRegisters[pin.port], pin.pin);
}

void DIO_writePin(PinInfo pin, u8 val) {
	if (val)
		SET_BIT(*DIO_OutRegisters[pin.port], pin.pin);
	else
		CLR_BIT(*DIO_OutRegisters[pin.port], pin.pin);
}

void DIO_togglePin(PinInfo pin) {
	TOG_BIT(*DIO_OutRegisters[pin.port], pin.pin);
}

void DIO_setPortSectionDirection(PortSectionInfo portsec, u8 dir) {
	if (dir)
		SET_BITS(*DIO_DirRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset);
	else
		CLR_BITS(*DIO_DirRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset);

	DIO_writeAllPinsPortSection(portsec, !dir);
}

void DIO_assignPortSectionDirection(PortSectionInfo portsec, u8 dirs) {
	ASS_BITS(*DIO_DirRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset, dirs);
	
	DIO_assignPortSection(portsec, ~dirs);
}

u8 DIO_readPortSection(PortSectionInfo portsec) {
	return GET_BITS(*DIO_InRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset);
}

void DIO_writeAllPinsPortSection(PortSectionInfo portsec, u8 val) {
	if (val)
		SET_BITS(*DIO_OutRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset);
	else
		CLR_BITS(*DIO_OutRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset);
}

void DIO_assignPortSection(PortSectionInfo portsec, u8 vals) {
	ASS_BITS(*DIO_OutRegisters[portsec.port], portsec.pinNumber, portsec.pinOffset, vals);
}
