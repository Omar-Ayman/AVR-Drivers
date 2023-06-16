
#include <VL/Types.h>
#include <VL/MCU.h>
#include <MCAL/UART/UART.h>

int main() {
    UART_initCustom(UART_BAUD_RATE_DEFAULT, UART_TransmitOnly, UART_PARITY_DEFAULT, UART_DATA_LENGTH_DEFAULT, UART_STOP_BITS_DEFAULT);
    UART_writeString("Hello UART!");

    while (1) {
        _delay_ms(1000);
    }
    return 0;
}
