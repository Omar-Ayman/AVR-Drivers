
#include <VL/MCU.h>
#include <MCAL/ADC/ADC.h>
#include <HAL/LCD/LCD.h>

LCD lcd = {{PORTC_IDX}, {PORTD_IDX, PIN4_IDX}, {PORTD_IDX, PIN5_IDX}, {PORTD_IDX, PIN6_IDX}};
PinInfo inpin = {PORTA_IDX, PIN0_IDX};
uint16_t dataint;
char datastr[7];

void myitoa(uint16_t x, char *str) {
    int16_t i;
    if (!x) {
        i = 3;
        str[4] = '0';
    } else {
        for (i = 4; x; --i, x /= 10)
            str[i] = (x % 10) + '0';
    }
    for (; i >= 0; --i)
        str[i] = ' ';
}

int main() {
    LCD_init(&lcd);
    ADC_init(inpin);
    
    datastr[5] = '%';
    datastr[6] = 0;

    while (1) {
        dataint = ADC_readPin(inpin);
        myitoa(((u32)dataint * 100) / ADC_MAX_VALUE, datastr);
        LCD_resetCursor(&lcd);
        LCD_writeString(&lcd, datastr);
        _delay_ms(10);
    }

    return 0;
}
