
#include "Keypad_prv.h"

#include <VL/BitArithmetics.h>

static const char Keypad_defaultCharMap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

u8 firstSetBit(u8 x) {
    u8 res;
    x = x & -x;
    for (res = 0; !(x & 1); x >>= 1, ++res);
    return res;
}

void Keypad_init(Keypad *keypad) {
    DIO_setPortSectionDirection(keypad->rows, OUTPUT);
    DIO_setPortSectionDirection(keypad->columns, INPUT);

    if (!keypad->charMap)
        keypad->charMap = (const char *)Keypad_defaultCharMap;
}

char Keypad_getFirstPressedKey(Keypad *keypad) {
    u8 row, col,
        baseRows = ONES(keypad->rows.pinNumber),
        baseCols = ONES(keypad->columns.pinNumber),
        colsNumber = keypad->columns.pinNumber ? keypad->columns.pinNumber : 8,
        lastRowPin = keypad->rows.pinOffset + (keypad->rows.pinNumber ? keypad->rows.pinNumber : 8);

    for (row = keypad->rows.pinOffset; row < lastRowPin; ++row) {
        DIO_assignPortSection(keypad->rows, baseRows & ~(1 << row));
        col = baseCols & ~DIO_readPortSection(keypad->columns);
        if (col)
            return *(keypad->charMap + (row - keypad->rows.pinOffset) * colsNumber + firstSetBit(col));
    }

    return 0;
}

u8 Keypad_getAllPressedKeys(Keypad *keypad, char *arr) {
    u8 row, col, i, j, resLen = 0,
        baseRows = ONES(keypad->rows.pinNumber),
        baseCols = ONES(keypad->columns.pinNumber),
        colsNumber = keypad->columns.pinNumber ? keypad->columns.pinNumber : 8,
        lastRowPin = keypad->rows.pinOffset + (keypad->rows.pinNumber ? keypad->rows.pinNumber : 8);

    for (row = keypad->rows.pinOffset, i = 0; row < lastRowPin; ++row, ++i) {
        DIO_assignPortSection(keypad->rows, baseRows & ~(1 << row));
        col = baseCols & ~DIO_readPortSection(keypad->columns);
        for (j = 0; j < colsNumber; ++j)
            if (GET_BIT(col, j))
                arr[resLen++] = *(keypad->charMap + i * colsNumber + j);
    }

    // arr[resLen] = 0;
    return resLen;
}
