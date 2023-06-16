#ifndef _SEVEN_SEGMENT_H
#define _SEVEN_SEGMENT_H

#include <VL/Types.h>
#include <MCAL/DIO/DIO.h>

typedef ENUM_PACKED SevenSegmentType {
    SevenSegment_CommonAnode,
    SevenSegment_CommonCathode
} SevenSegmentType;

typedef ENUM_PACKED SevenSegmentErrorCode {
    SevenSegment_NoError = 0,
    SevenSegment_SmallPinNumber = 1,
    SevenSegment_PinOffsetShifted,
    SevenSegment_UndefinedType,
    SevenSegment_MultipleDigits,
    SevenSegment_SmallSegsArray
} SevenSegmentErrorCode;

typedef struct SevenSegment {
    PortSectionInfo port;
    SevenSegmentType type;
} SevenSegment;

SevenSegmentErrorCode SevenSegment_init(SevenSegment *sevseg);

SevenSegmentErrorCode SevenSegment_initArr(SevenSegment *segsv, u8 segsc);

SevenSegmentErrorCode SevenSegment_clear(SevenSegment *sevseg);

SevenSegmentErrorCode SevenSegment_writeDigit(SevenSegment *sevseg, u8 x);

SevenSegmentErrorCode SevenSegment_writeNumber(SevenSegment *segsv, u8 segsc, u16 x);

#endif