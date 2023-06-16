
#ifndef _KEYPAD_H
#define _KEYPAD_H

#include <MCAL/DIO/DIO.h>
#include <VL/Types.h>

typedef struct Keypad {
    PortSectionInfo rows;
    PortSectionInfo columns;
    const char *charMap;
} Keypad;

void Keypad_init(Keypad *keypad);

char Keypad_getFirstPressedKey(Keypad *keypad);

u8 Keypad_getAllPressedKeys(Keypad *keypad, char *arr);

#endif