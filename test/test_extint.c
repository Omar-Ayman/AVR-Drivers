
#include <MCAL/ExternalInterrupt/ExternalInterrupt.h>

volatile u8 i = 0;
PinInfo led = {PORTB_IDX, PIN0_IDX};
PinInfo btn = INT1_PIN_INFO;

void handle() {
    i = (i + 1) % 2;
}

int main() {
    ExternalInterrupt_setupPin(btn, ExternalInterrupt_onChange, handle);
    DIO_setPinDirection(led, OUTPUT);

    while (1) {
        DIO_writePin(led, i);
        _delay_ms(50);
    }
}
