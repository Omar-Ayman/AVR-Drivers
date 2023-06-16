
#include <VL/MCU.h>
#include <HAL/LCD/LCD.h>

u8 t;
char tstr[10];
LCD lcd = {{PORTD_IDX, 0, 0}, {PORTC_IDX, 0}, {PORTC_IDX, 1}, {PORTC_IDX, 2}};

int main() {
    LCD_init(&lcd);
    
    char name[] = "Omar Ayman";
    char temp[2] = "a";

    for (t = 0; name[t]; ++t) {
        temp[0] = name[t];
        LCD_setCursorPos(&lcd, t, t % 2);
        LCD_writeString(&lcd, temp);
    }

    while (1) {
        // itoa(t++, tstr, 10);
        // LCD_setCursorPos(&lcd, 7, 0);
        // LCD_writeString(&lcd, tstr);
        // _delay_ms(1000);
    }

    return 0;
}
