
#include <VL/MCU.h>
#include <HAL/Keypad/Keypad.h>
#include <HAL/LCD/LCD.h>
#include <HAL/SevenSegment/SevenSegment.h>

const char myKeypadMap[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

char str[10];
LCD lcd = {{PORTA_IDX, 0, 0}, {PORTB_IDX, PIN0_IDX}, {PORTB_IDX, PIN1_IDX}, {PORTB_IDX, PIN2_IDX}};
Keypad keypad = {{PORTC_IDX, 4, PIN0_IDX}, {PORTC_IDX, 3, PIN4_IDX}, (const char *)myKeypadMap};
SevenSegment sevseg = {{PORTD_IDX, 0, 0}, SevenSegment_CommonAnode};

int main() {
    LCD_init(&lcd);
    Keypad_init(&keypad);
    SevenSegment_init(&sevseg);
    str[1] = 0;

    while (1) {
        str[0] = Keypad_getFirstPressedKey(&keypad);
        if (!str[0])
            str[0] = '?';
        LCD_setCursorPos(&lcd, 0, 0);
        LCD_writeString(&lcd, str);
        if (str[0] >= '0' && str[0] <= '9')
            SevenSegment_writeDigit(&sevseg, str[0] - '0');
        else
            SevenSegment_clear(&sevseg);
        _delay_ms(10);
    }

    return 0;
}
