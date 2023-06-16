
#ifndef _LCD_PRV_H
#define _LCD_PRV_H

#include "LCD.h"

#define FULL_COMMAND_PERIOD 2000
#define HALF_COMMAND_PERIOD 500

void LCD_execCommand(LCD *lcd, u16 cmdPeriodUs);

u8 LCD_readCommand(LCD *lcd, u8 rs);

void LCD_writeCommand(LCD *lcd, u8 rs, u8 cmd);

#endif
