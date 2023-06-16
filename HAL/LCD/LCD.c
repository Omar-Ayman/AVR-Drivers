
#include "LCD_prv.h"
#include <stdlib.h>

#include <VL/MCU.h>
#include "LCD.h"

char tempstr[16];

void LCD_execCommand(LCD *lcd, u16 cmdPeriodUs) {
    DIO_writePin(lcd->E, HIGH);
    _delay_us(cmdPeriodUs);
    DIO_writePin(lcd->E, LOW);
    _delay_us(cmdPeriodUs);
}

u8 LCD_readCommand(LCD *lcd, u8 rs) {
    u8 res = 0;
    DIO_writePin(lcd->RS, rs);
    DIO_writePin(lcd->RW, HIGH);

    DIO_writePin(lcd->E, HIGH);
    _delay_ms(HALF_COMMAND_PERIOD);

    if (lcd->mode == LCD_8BitMode) {
        res = DIO_readPortSection(lcd->D);
    } else {
        res = DIO_readPortSection(lcd->D) << 4;
        DIO_writePin(lcd->E, LOW);
        _delay_ms(HALF_COMMAND_PERIOD);
        DIO_writePin(lcd->E, HIGH);
        _delay_ms(HALF_COMMAND_PERIOD);
        res |= DIO_readPortSection(lcd->D);
    }

    DIO_writePin(lcd->E, LOW);
    _delay_ms(HALF_COMMAND_PERIOD);

    return res;
}

void LCD_writeCommand(LCD *lcd, u8 rs, u8 cmd) {
    DIO_writePin(lcd->RS, rs);
    DIO_writePin(lcd->RW, LOW);

    if (lcd->mode == LCD_8BitMode) {
        DIO_assignPortSection(lcd->D, cmd);
    } else {
        DIO_assignPortSection(lcd->D, cmd >> 4);
        LCD_execCommand(lcd, HALF_COMMAND_PERIOD);
        DIO_assignPortSection(lcd->D, cmd);
    }
    LCD_execCommand(lcd, FULL_COMMAND_PERIOD);
}

void LCD_init(LCD *lcd) {
    if (lcd->D.pinNumber == 0) {
        lcd->D.pinOffset = 0;
        lcd->mode = LCD_8BitMode;
    } else {
        lcd->D.pinNumber = 4;
        lcd->mode = LCD_4BitMode;
    }

    DIO_setPinDirection(lcd->RS, OUTPUT);
    DIO_setPinDirection(lcd->RW, OUTPUT);
    DIO_setPinDirection(lcd->E, OUTPUT);
    DIO_setPortSectionDirection(lcd->D, OUTPUT);
    
    _delay_ms(30);
    
    DIO_writePin(lcd->RS, LOW);
    DIO_writePin(lcd->RW, LOW);

    if (lcd->mode == LCD_8BitMode) {
        DIO_assignPortSection(lcd->D, 0x3c);
        LCD_execCommand(lcd, FULL_COMMAND_PERIOD);
    } else {
        DIO_assignPortSection(lcd->D, 0x2);
        LCD_execCommand(lcd, HALF_COMMAND_PERIOD);
        DIO_assignPortSection(lcd->D, 0x2);
        LCD_execCommand(lcd, HALF_COMMAND_PERIOD);
        DIO_assignPortSection(lcd->D, 0xc);
        LCD_execCommand(lcd, FULL_COMMAND_PERIOD);
    }
    
    LCD_setDisplayState(lcd, 1);

    LCD_clearDisplay(lcd);

    LCD_writeCommand(lcd, LOW, 0x06);
}

void LCD_clearDisplay(LCD *lcd) {
    LCD_writeCommand(lcd, LOW, 0x01);
}

void LCD_resetCursor(LCD *lcd) {
    LCD_writeCommand(lcd, LOW, 0x02);
}

void LCD_setCursorPos(LCD *lcd, u8 x, u8 y) {
    if (x < 16 && y < 2)
        LCD_writeCommand(lcd, LOW, 0x80 | (x + y * 0x40));
}

// void LCD_setCursorDisplay(LCD *lcd, uint8_t on) {
// }

// void LCD_setCursorBlinking(LCD *lcd, uint8_t on) {
// }

void LCD_setDisplayState(LCD *lcd, u8 on) {
    LCD_writeCommand(lcd, LOW, 0x08 | (on ? 6 : 0));
}

void LCD_shiftDisplay(LCD *lcd, u8 shift, LCD_ShiftDirection direction) {
    while (shift--)
        LCD_writeCommand(lcd, LOW, 0x18 | direction);
}

void LCD_writeChar(LCD *lcd, char c) {
    LCD_writeCommand(lcd, HIGH, c);
}

// void LCD_writeInteger(LCD *lcd, s64 n) {
//     LCD_writeIntegerToBase(lcd, n, 10);
// }

void LCD_writeIntegerToBase(LCD *lcd, s64 n, u8 base) {
    itoa(n, tempstr, base);
    LCD_writeString(lcd, tempstr);
}

void LCD_writeString(LCD *lcd, char *str) {
    if (!str || !*str)
        return;

    while (*str)
        LCD_writeCommand(lcd, HIGH, *(str++));
}

void LCD_writeNonAsciiString(LCD *lcd, u8 (*chars)[8], u8 len, LCD_FlowDirection dir) {
    u8 currAdr, i, j, k, start;
    s8 inr;
    
    if (dir == LCD_LTR) {
        start = 0;
        inr = 1;
    } else {
        start = len - 1;
        inr = -1;
    }
    
    DIO_setPortSectionDirection(lcd->D, INPUT);
    currAdr = LCD_readCommand(lcd, LOW);
    DIO_setPortSectionDirection(lcd->D, OUTPUT);
    
    for (i = 0; i < len; i += 8) {
        LCD_writeCommand(lcd, LOW, 0x40);

        for (j = 0; j < 8 && (i + j) < len; ++j)
            for (k = 0; k < 8; ++k)
                LCD_writeCommand(lcd, HIGH, chars[start + (i + j) * inr][k]);
                
        LCD_writeCommand(lcd, LOW, 0x80 | (currAdr + i));

        for (j = 0; j < 8 && (i + j) < len; ++j)
            LCD_writeCommand(lcd, HIGH, j);
    }
}
