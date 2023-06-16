
#include <MCAL/ADC/ADC.h>
#include <MCAL/PWM/PWM_prv.h>
#include <HAL/LCD/LCD.h>

#include <VL/MCU.h>

LCD lcd = {{PORTC_IDX}, {PORTD_IDX, 0}, {PORTD_IDX, 1}, {PORTD_IDX, 2}};
PinInfo inpin = {PORTA_IDX, PIN0_IDX};
PinInfo outpin = {PORTD_IDX, PIN3_IDX};
u32 testdata;
u8 data;
PWMCustomHandle pwm;
// extern u8 totalCustomValues[2];
// extern u8 limitCustomValues[2][2];

int main() {
    LCD_init(&lcd);
    ADC_init(inpin);
    pwm = PWMCustom_init(outpin, 50);

    while (1) {
        LCD_clearDisplay(&lcd);
        testdata = ADC_readValue(inpin);
        data = (testdata * PWM_MAX_DUTY_CYCLE) / ADC_MAX_VALUE;
        PWMCustom_writeDutyCycle(pwm, data);
        
        // LCD_resetCursor(&lcd);
        // LCD_writeIntegerToBase(&lcd, totalCustomValues[pwm], 10);
        // LCD_setCursorPos(&lcd, 0, 1);
        // LCD_writeIntegerToBase(&lcd, limitCustomValues[pwm][1], 10);
        // LCD_setCursorPos(&lcd, 5, 0);
        // LCD_writeIntegerToBase(&lcd, limitCustomValues[pwm][0], 10);
        LCD_setCursorPos(&lcd, 5, 1);
        LCD_writeIntegerToBase(&lcd, *TCCR0_RAW, 10);

        _delay_ms(100);
    }

    return 0;
}
