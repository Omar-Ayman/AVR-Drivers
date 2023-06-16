#ifndef _I2C_H
#define _I2C_H

#include <VL/Types.h>

#define I2C_MAX_CLK_FREQ 400000
#define I2C_MIN_CLK_FREQ (F_CPU / 36)

void I2C_init(u8 address, u8 enableGeneralCall, u32 clkFreq);

u8 I2C_masterTransmit(u8 slaveAddress, u8 *data, u8 dataLen);

#endif