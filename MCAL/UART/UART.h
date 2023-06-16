#ifndef _UART_H
#define _UART_H

#include <MCAL/DIO/DIO.h>

#define RX_PIN_INFO {PORTD_IDX, PIN0_IDX}
#define TX_PIN_INFO {PORTD_IDX, PIN1_IDX}

#define UART_BAUD_RATE_DEFAULT 9600
#define UART_MODE_DEFAULT UART_TransmitRecive
#define UART_PARITY_DEFAULT UART_NoParity
#define UART_DATA_LENGTH_DEFAULT UART_8BitData
#define UART_STOP_BITS_DEFAULT UART_1StopBit

typedef ENUM_PACKED UART_Mode {
    UART_TransmitRecive = 0b11,
    UART_TransmitOnly = 0b01,
    UART_ReciveOnly = 0b10,
} UART_Mode;

typedef ENUM_PACKED UART_Parity {
    UART_NoParity = 0b00,
    UART_EvenParity = 0b10,
    UART_OddParity = 0b11,
} UART_Parity;

typedef ENUM_PACKED UART_DataLength {
    UART_5BitData = 0b000,
    UART_6BitData = 0b001,
    UART_7BitData = 0b010,
    UART_8BitData = 0b011,
    // UART_9BitData = 0b111,
} UART_DataLength;

typedef ENUM_PACKED UART_StopBits {
    UART_1StopBit = 0,
    UART_2StopBits = 1,
} UART_StopBits;

void UART_initDefault();
void UART_init(u32 baudRate);
void UART_initCustom(u32 baudRate, UART_Mode mode, UART_Parity parity, UART_DataLength dataLen, UART_StopBits stopBit);

void UART_writeByte(u8 data);
void UART_writeBytes(u8 *data, u32 dataLen);
void UART_writeString(char *str);

u8 UART_readByteAwait();
u8 UART_readByte(u8 *dataPtr);
void UART_readBytesAwait(u8 *data, u32 dataLen);
u8 UART_readBytes(u8 *data, u32 dataLen);
void UART_readString(char *str, u32 maxLen);

#endif