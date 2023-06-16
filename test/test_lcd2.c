
#include <VL/MCU.h>
#include <HAL/LCD/LCD.h>

LCD lcd = {{PORTD_IDX, 0, 0}, {PORTC_IDX, 0}, {PORTC_IDX, 1}, {PORTC_IDX, 2}};
u8 str[][8] = {
    {0, 0, 3, 4, 4, 31,  0,  0},
    {0, 0, 0, 0, 0, 31, 10,  4},
    {0, 0, 0, 8, 4,  7,  4, 24}
};

int main() {
    LCD_init(&lcd);
    LCD_setCursorPos(&lcd, 5, 0);
    // LCD_writeString(&lcd, "hello");
    LCD_writeNonAsciiString(&lcd, str, 3, LCD_RTL);

    while (1) {

    }
}
