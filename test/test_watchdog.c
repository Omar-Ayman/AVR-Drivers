
#include <VL/MCU.h>
#include <MCAL/WatchdogTimer/WatchdogTimer.h>
#include <MCAL/DIO/DIO.h>

PinInfo led = {PORTB_IDX, PIN0_IDX};

int main() {
    DIO_setPinDirection(led, OUTPUT);
    _delay_ms(1000);
    DIO_writePin(led, HIGH);
    WatchdogTimer_start(WatchdogTimer_1024k);
    while (1) {
        _delay_ms(1000);
        WatchdogTimer_restart(WatchdogTimer_1024k);
    }
    return 0;
}
