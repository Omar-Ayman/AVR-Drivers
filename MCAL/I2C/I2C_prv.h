#ifndef _I2C_PRV_H
#define _I2C_PRV_H

#include "I2C.h"
#include <VL/MCU.h>

#define SLA_W(SLA) (SLA << 1)
#define SLA_R(SLA) ((SLA << 1) | 1)

typedef ENUM_PACKED I2C_StatusCode {
    I2C_StartConditionTransmitted = 0x01,
    I2C_RepeatedStartConditionTransmitted = 0x02,
    I2C_SLA_W_TransmittedAckRecived = 0x03,
    I2C_SLA_W_TransmittedNackRecived = 0x04,
    I2C_ByteTransmittedAckRecived = 0x05,
    I2C_ByteTransmittedNackRecived = 0x06,
    I2C_ArbitrationLost = 0x07,
    I2C_SLA_R_TransmittedAckRecived = 0x08,
    I2C_SLA_R_TransmittedNackRecived = 0x09,
    I2C_ByteRecivedAckReturned = 0x0a,
    I2C_ByteRecivedNackReturned = 0x0b,
} I2C_StatusCode;

struct TWCR_RegStruct {
    u8 TWIE_pin : 1;
    u8 _reserved: 1;
    u8 TWEN_pin : 1;
    u8 TWWC_pin : 1;
    u8 TWSTO_pin : 1;
    u8 TWSTA_pin : 1;
    u8 TWEA_pin : 1;
    u8 TWINT_pin : 1;
};

struct TWSR_RegStruct {
    u8 TWPS_pins : 2;
    u8 _reserved : 1;
    u8 TWS_pins : 5;
};

struct TWAR_RegStruct {
    u8 TWGCE_pin : 1;
    u8 TWA_pins : 7;
};

#define TWBR_REG (*((volatile u8 *)0x20))
#define TWCR_REG (*((volatile struct TWCR_RegStruct *)0x56))
#define TWSR_REG (*((volatile struct TWSR_RegStruct *)0x21))
#define TWDR_REG (*((volatile u8 *)0x23))
#define TWAR_REG (*((volatile struct TWAR_RegStruct *)0x22))

void I2C_setClockFrequency(u32 fr);

u8 I2C_startCondition();
u8 I2C_masterWriteAdderss(u8 slaveAddress);
u8 I2C_masterWriteByte(u8 data);
void I2C_stopCondition();

#endif