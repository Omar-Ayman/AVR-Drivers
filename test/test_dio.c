
#include <VL/MCU.h>
#include <MCAL/DIO/DIO.h>

uint8_t mode, prevMode = -1, state;

PortSectionInfo leds = {PORTD_IDX};
PortSectionInfo dips = {PORTC_IDX, 3, PIN3_IDX};

int main() {
    DIO_setPortSectionDirection(leds, OUTPUT);
    DIO_setPortSectionDirection(dips, INPUT);

    while (1) {
        mode = DIO_readPortSection(dips);
        if (mode != prevMode) {
            state = 0;
            prevMode = mode;
        }
        switch (mode)
        {
        case 0:
            DIO_assignPortSection(leds, (0x80 >> state) | (0x01 << state));
            state = (state + 1) % 8;
            _delay_ms(300);
            break;
        
        case 1:
            state = ~state;
            DIO_assignPortSection(leds, state);
            _delay_ms(500);
            break;
        
        case 2:
            DIO_assignPortSection(leds, 0x01 << state);
            state = (state + 1) % 8;
            _delay_ms(250);
            break;
        
        case 3:
            DIO_assignPortSection(leds, 0x80 >> state);
            state = (state + 1) % 8;
            _delay_ms(250);
            break;
        
        case 4:
            DIO_assignPortSection(leds, (0x80 >> state) | (0x01 << state));
            state = (state + 1) % 4;
            _delay_ms(300);
            break;
        
        case 5:
            DIO_assignPortSection(leds, (0x10 << state) | (0x08 >> state));
            state = (state + 1) % 4;
            _delay_ms(300);
            break;
        
        case 6:
            DIO_assignPortSection(leds, (0x80 >> state) | (0x01 << state));
            state = (state + 1) % 7;
            if (state == 4)
                state = 5;
            _delay_ms(250);
            break;
        
        case 7:
            DIO_assignPortSection(leds, 0xff >> (7 - state));
            state = (state + 1) % 8;
            _delay_ms(300);
            break;
        }
    }

    return 0;
}
