
#include <VL/MCU.h>
#include <HAL/SevenSegment/SevenSegment.h>

SevenSegment sevenSegments[] = {{{PORTA_IDX}, SevenSegment_CommonAnode}, {{PORTB_IDX}, SevenSegment_CommonAnode}};
uint8_t sevenSegmentsCount = sizeof(sevenSegments) / sizeof(SevenSegment);

PinInfo redLight = {PORTC_IDX, PIN0_IDX};
PinInfo yellowLight = {PORTC_IDX, PIN1_IDX};
PinInfo greenLight = {PORTC_IDX, PIN2_IDX};

uint8_t t;

int main() {
    SevenSegment_initArr(sevenSegments, sevenSegmentsCount);
    DIO_setPinDirection(redLight, OUTPUT);
    DIO_setPinDirection(yellowLight, OUTPUT);
    DIO_setPinDirection(greenLight, OUTPUT);

    while (1) {
        DIO_writePin(greenLight, LOW);
        DIO_writePin(redLight, HIGH);
        for (t = 10; t > 0; --t) {
            SevenSegment_writeNumber(sevenSegments, sevenSegmentsCount, t);
            _delay_ms(1000);
        }
        
        DIO_writePin(redLight, LOW);
        DIO_writePin(yellowLight, HIGH);
        for (t = 3; t > 0; --t) {
            SevenSegment_writeNumber(sevenSegments, sevenSegmentsCount, t);
            _delay_ms(1000);
        }
        
        DIO_writePin(yellowLight, LOW);
        DIO_writePin(greenLight, HIGH);
        for (t = 10; t > 0; --t) {
            SevenSegment_writeNumber(sevenSegments, sevenSegmentsCount, t);
            _delay_ms(1000);
        }
    }

    return 0;
}
