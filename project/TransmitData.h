#ifndef _TRANSMIT_DATA_H
#define _TRANSMIT_DATA_H

#include <VL/Types.h>

typedef struct TransmitData {
    u16 adcVal : 10;
    u16 intState0 : 1;
    u16 intState1 : 1;
    u16 keyPressed : 4;
} TransmitData;

#endif