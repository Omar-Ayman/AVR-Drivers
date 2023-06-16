
#include "UART_prv.h"
#include "UART.h"
#include <avr/interrupt.h>

#define UART_BUFFER_SIZE 128
static volatile u8 _buffer[UART_BUFFER_SIZE];
static volatile u8 _last = 0;
static volatile u8 _size = 0;

ISR_HNDL(UART_RXC_ISR_VCT) {
    if (_size < UART_BUFFER_SIZE) {
        _buffer[_last] = UDR_REG;
        _last = (_last + 1) % UART_BUFFER_SIZE;
        ++_size;
    }
}

u8 UART_dequeueBufferAtomic() {
    u8 data;
    UCSRB_REG.aXCIE_pins = 0;
    data = _buffer[(_last + UART_BUFFER_SIZE - _size--) % UART_BUFFER_SIZE];
    UCSRB_REG.aXCIE_pins = UART_ReciveOnly;
    return data;
}

u8 UART_consumeBufferAwait()
{
    while (!_size);
    return UART_dequeueBufferAtomic();
}

u8 UART_consumeBuffer(u8 *dataPtr) {
    if (!_size)
        return 0;

    *dataPtr = UART_dequeueBufferAtomic();
    return 1;
}

void UART_initDefault() {
    UART_init(UART_BAUD_RATE_DEFAULT);
}

void UART_init(u32 baudRate) {
    UART_initCustom(baudRate, UART_MODE_DEFAULT, UART_PARITY_DEFAULT, UART_DATA_LENGTH_DEFAULT, UART_STOP_BITS_DEFAULT);
}

void UART_initCustom(u32 baudRate, UART_Mode mode, UART_Parity parity, UART_DataLength dataLen, UART_StopBits stopBit) {
    // turn on recive interrupt
    SREG_REG.I_pin = 1;
    UCSRB_REG.aXCIE_pins = UART_ReciveOnly;
    UCSRB_REG.UDRIE_pin = 0;

    // set baud rate
    UART_setBaudRate(baudRate);

    // enable UART
    UCSRC_REG.UMSEL_pin = 0;
    UCSRC_REG.UCPOL_pin = 0;

    // set send recive mode
    UCSRB_REG.aXEN_pins = mode;

    // set parity
    UCSRC_REG.URSEL_pin = URSEL_UCSRC;
    UCSRC_REG.UPM_pins = parity;

    // set data length
    UCSRC_REG.UCSZ_pins = dataLen;
    UCSRB_REG.UCSZ2_pin = dataLen >> 2;

    // set stop bit
    UCSRC_REG.USBS_pin = stopBit;
}

void UART_setBaudRate(u32 baudRate) {
    UCSRA_REG.U2X_pin = 0;
    baudRate = (F_CPU >> 4) / baudRate - 1;
    UBRRL_REG = baudRate;
    UBRRH_REG.URSEL_pin = URSEL_UBRRH;
    UBRRH_REG.UBRRH_pins = baudRate >> 8;
}

void UART_writeByte(u8 data) {
    while (!UCSRA_REG.UDER_pin);
    UDR_REG = data;
}

void UART_writeBytes(u8 *data, u32 dataLen) {
    u32 i;
    for (i = 0; i < dataLen; ++i)
        UART_writeByte(data[i]);
}

void UART_writeString(char *str) {
    while (*str)
        UART_writeByte(*(str++));
    UART_writeByte(0);
}
     
u8 UART_readByteAwait() {
    return UART_consumeBufferAwait();
}

u8 UART_readByte(u8 *dataPtr) {
    return UART_consumeBuffer(dataPtr);
}

void UART_readBytesAwait(u8 *data, u32 dataLen) {
    u32 i;
    for (i = 0; i < dataLen; ++i)
        data[i] = UART_readByteAwait();
}

u8 UART_readBytes(u8 *data, u32 dataLen) {
    u8 res = 1;
    if (_size < dataLen)
        return 0;

    while (res && dataLen--)
        res &= UART_readByte(data++);

    return res;
}

void UART_readString(char *str, u32 maxLen) {
    u32 i;
    if (!maxLen)
        do { *str = UART_readByteAwait(); } while (*(str++));
    else {
        for (i = 0; i < maxLen; ++i, ++str) {
            *str = UART_readByteAwait();
            if (!str)
                break;
        }
    }
}
