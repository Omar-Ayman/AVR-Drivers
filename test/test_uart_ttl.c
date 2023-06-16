
#include <VL/MCU.h>
#include <MCAL/UART/UART.h>
#include <HAL/Keypad/Keypad.h>
#include <HAL/LCD/LCD.h>

char charmap[4][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}, {'*', '0', '#'}};

Keypad keypad = {{PORTC_IDX, 4, PIN0_IDX}, {PORTC_IDX, 3, PIN4_IDX}, (const char *)charmap};
LCD lcd = {{PORTA_IDX}, {PORTB_IDX, PIN0_IDX}, {PORTB_IDX, PIN1_IDX}, {PORTB_IDX, PIN2_IDX}};
char inChar;
char prevChar;
u8 i = 0;
char outChar;
u8 check;

int main() {
    UART_initDefault();
    Keypad_init(&keypad);
    LCD_init(&lcd);

    while (1) {
        inChar = Keypad_getFirstPressedKey(&keypad);
        if (inChar != prevChar) {
            prevChar = inChar;
            if (inChar) {
                UART_writeByte(inChar);
                UART_writeByte('\r');
                UART_writeByte('\n');
            }
        }

        check = UART_readByte(&outChar);
        if (check) {
            ++i;
            if (i >= 16) {
                i = 0;
                LCD_resetCursor(&lcd);
            }
            LCD_writeChar(&lcd, outChar);
            UART_writeByte(outChar);
            UART_writeByte('\r');
            UART_writeByte('\n');
        }

        _delay_ms(10);
    }
    return 0;
}
