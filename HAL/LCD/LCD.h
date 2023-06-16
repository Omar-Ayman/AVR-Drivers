
#ifndef _LCD_H
#define _LCD_H

#include <MCAL/DIO/DIO.h>

typedef ENUM_PACKED LCD_Mode {
    LCD_4BitMode = 0,
    LCD_8BitMode = 1
} LCD_Mode;

typedef ENUM_PACKED LCD_ShiftDirection {
    LCD_ShiftLeft = 0x0,
    LCD_ShiftRight = 0x4
} LCD_ShiftDirection;

typedef ENUM_PACKED LCD_FlowDirection {
    LCD_LTR = 0,
    LCD_RTL = 1
} LCD_FlowDirection;

typedef struct LCD {
    PortSectionInfo D;
    PinInfo RS;
    PinInfo RW;
    PinInfo E;
    LCD_Mode mode;
} LCD;

void LCD_init(LCD *lcd);

void LCD_clearDisplay(LCD *lcd);

void LCD_resetCursor(LCD *lcd);

void LCD_setCursorPos(LCD *lcd, u8 x, u8 y);

// void LCD_setCursorDisplay(LCD *lcd, uint8_t on);

// void LCD_setCursorBlinking(LCD *lcd, uint8_t on);

void LCD_setDisplayState(LCD *lcd, u8 on);

void LCD_shiftDisplay(LCD *lcd, u8 shift, LCD_ShiftDirection direction);

void LCD_writeChar(LCD *lcd, char c);

// void LCD_writeInteger(LCD *lcd, s64 n);

void LCD_writeIntegerToBase(LCD *lcd, s64 n, u8 base);

void LCD_writeString(LCD *lcd, char *str);

void LCD_writeNonAsciiString(LCD *lcd, u8 (*chars)[8], u8 len, LCD_FlowDirection dir);

#endif