
#include <VL/Types.h>
#include <VL/MCU.h>
#include <MCAL/UART/UART.h>
#include <HAL/LCD/LCD.h>

#include <stdlib.h>

LCD lcd = {{PORTA_IDX}, {PORTB_IDX, PIN0_IDX}, {PORTB_IDX, PIN1_IDX}, {PORTB_IDX, PIN2_IDX}};
char str[17] = "?";

int main() {
    UART_initCustom(UART_BAUD_RATE_DEFAULT, UART_ReciveOnly, UART_PARITY_DEFAULT, UART_DATA_LENGTH_DEFAULT, UART_STOP_BITS_DEFAULT);
    LCD_init(&lcd);
    _delay_ms(3000);
    UART_readString(str, 0);
    LCD_writeString(&lcd, str);

    while (1) {
        _delay_ms(1000);
    }
    return 0;
}
