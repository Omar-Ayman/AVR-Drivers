
#include <MCAL/DIO/DIO.h>
#include <VL/MCU.h>

PinInfo outPin = {PORTB_IDX, PIN0_IDX};

int main() {
    DIO_setPinDirection(outPin, OUTPUT);

    while (1) {
        _delay_ms(1000);
        DIO_togglePin(outPin);
    }

    return 0;
}
