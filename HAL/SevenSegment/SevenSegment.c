
#include "SevenSegment.h"

// #define SEVSEG_MAX_CHARS 4

u8 SevenSegment_digitMap_cc[10] = { 
    0b0111111,
    0b0000110,
    0b1011011,
    0b1001111,
    0b1100110,
    0b1101101,
    0b1111101,
    0b0000111,
    0b1111111,
    0b1101111
};

SevenSegmentErrorCode SevenSegment_init(SevenSegment *sevseg) {
    if (sevseg->port.pinNumber)
        return SevenSegment_SmallPinNumber;

    if (sevseg->port.pinOffset)
        return SevenSegment_PinOffsetShifted;

    if (sevseg->type != SevenSegment_CommonAnode && sevseg->type != SevenSegment_CommonCathode)
        return SevenSegment_UndefinedType;
        
    DIO_setPortSectionDirection(sevseg->port, OUTPUT);
    return SevenSegment_NoError;
}

SevenSegmentErrorCode SevenSegment_initArr(SevenSegment *segsv, u8 segsc) {
    u8 i;
    s8 err;
    for (i = 0; i < segsc; ++i) {
        SevenSegment_init(segsv + i);

        if (err)
            return err;
    }

    return SevenSegment_NoError;
}

SevenSegmentErrorCode SevenSegment_clear(SevenSegment *sevseg) {
    if (sevseg->type != SevenSegment_CommonAnode && sevseg->type != SevenSegment_CommonCathode)
        return SevenSegment_UndefinedType;

    DIO_writeAllPinsPortSection(sevseg->port, (sevseg->type + 1) % 2);
    return SevenSegment_NoError;
}

SevenSegmentErrorCode SevenSegment_writeDigit(SevenSegment *sevseg, u8 x)
{
    if (sevseg->type != SevenSegment_CommonAnode && sevseg->type != SevenSegment_CommonCathode)
        return SevenSegment_UndefinedType;

    if (x > 9)
        return SevenSegment_MultipleDigits;

    DIO_assignPortSection(sevseg->port, SevenSegment_digitMap_cc[x] ^ (sevseg->type - 1));
    return SevenSegment_NoError;
}

SevenSegmentErrorCode SevenSegment_writeNumber(SevenSegment *segsv, u8 segsc, u16 x) {
    s8 i;
    SevenSegmentErrorCode err = SevenSegment_NoError;

    if (!segsc)
        return SevenSegment_SmallSegsArray;

    if (!x) {
        err = SevenSegment_writeDigit(segsv, 0);
        i = 1;
    } else {
        for (i = 0; x && !err; ++i, x /= 10) {
            if (i >= segsc) {
                err = SevenSegment_SmallSegsArray;
                break;
            }

            err = SevenSegment_writeDigit(segsv + i, x % 10);
        }
    }

    for (; i < segsc && !err; ++i)
        err = SevenSegment_clear(segsv + i);

    return err;
}
