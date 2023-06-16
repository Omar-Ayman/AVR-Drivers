
#ifndef _DIO_H
#define _DIO_H

#include <VL/Types.h>

/* Port Defines */
#define PORTA_IDX    0
#define PORTB_IDX    1
#define PORTC_IDX    2
#define PORTD_IDX    3

/* PIN Defines */
#define PIN0_IDX   0
#define PIN1_IDX   1
#define PIN2_IDX   2
#define PIN3_IDX   3
#define PIN4_IDX   4
#define PIN5_IDX   5
#define PIN6_IDX   6
#define PIN7_IDX   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0

/* Struct for saving pin info*/
typedef struct PinInfo {
    u8 port : 2;
    u8 pin : 3;
} PinInfo;

/* Struct for saving port section info*/
typedef struct PortSectionInfo {
    u8 port : 2;
    u8 pinNumber : 3;
    u8 pinOffset : 3;
} PortSectionInfo;

#define AS_U8(PIN) *((u8*)(&PIN))

void DIO_setPinDirection(PinInfo pin, u8 dir);

void DIO_setPinDirectionInitVal(PinInfo pin, u8 dir, u8 val);

u8 DIO_readPin(PinInfo pin);

void DIO_writePin(PinInfo pin, u8 val);

void DIO_togglePin(PinInfo pin);


void DIO_setPortSectionDirection(PortSectionInfo portsec, u8 dir);

void DIO_assignPortSectionDirection(PortSectionInfo portsec, u8 dirs);

u8 DIO_readPortSection(PortSectionInfo portsec);

void DIO_writeAllPinsPortSection(PortSectionInfo portsec, u8 val);

void DIO_assignPortSection(PortSectionInfo portsec, u8 vals);

#endif