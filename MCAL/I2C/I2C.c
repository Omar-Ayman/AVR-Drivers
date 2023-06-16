
#include "I2C_prv.h"

#include <math.h>

void I2C_init(u8 address, u8 enableGeneralCall, u32 clkFreq) {
    TWAR_REG.TWA_pins = address;
    TWAR_REG.TWGCE_pin = enableGeneralCall;
    TWCR_REG.TWEA_pin = 1;
    TWCR_REG.TWEN_pin = 1;

    I2C_setClockFrequency(clkFreq);
}

void I2C_setClockFrequency(u32 fr) {
    u32 div;
    u8 ps = 0;

    if (!fr) {
        TWBR_REG = 0;
        TWSR_REG.TWPS_pins = 0;
    }

    if (fr > I2C_MAX_CLK_FREQ)
        fr = I2C_MAX_CLK_FREQ;

    if (fr < I2C_MIN_CLK_FREQ)
        fr = I2C_MIN_CLK_FREQ;

    div = ((F_CPU) / fr - 16) >> 1;
    if (div >= (1 << 8))
        ps = logf(((f32)div) / (1 << 8)) / logf(2.0f);
    
    TWSR_REG.TWPS_pins = ps;
    TWBR_REG = div >> (ps << 1);
}

u8 I2C_startCondition() {
    TWCR_REG.TWSTA_pin = 1;
    TWCR_REG.TWSTO_pin = 0;
    TWCR_REG.TWEN_pin = 1;
    TWCR_REG.TWINT_pin = 1;
    
    while (!TWCR_REG.TWINT_pin);

    return TWSR_REG.TWS_pins != I2C_StartConditionTransmitted ? TWSR_REG.TWS_pins : 0;
}

u8 I2C_masterWriteAdderss(u8 slaveAddress) {
    TWDR_REG = SLA_W(slaveAddress);

    TWCR_REG.TWSTA_pin = 0;
    TWCR_REG.TWSTO_pin = 0;
    TWCR_REG.TWEN_pin = 1;
    TWCR_REG.TWINT_pin = 1;
    
    while (!TWCR_REG.TWINT_pin);

    return TWSR_REG.TWS_pins != I2C_SLA_W_TransmittedAckRecived ? TWSR_REG.TWS_pins : 0;
}

u8 I2C_masterWriteByte(u8 data) {
    TWDR_REG = data;

    TWCR_REG.TWSTA_pin = 0;
    TWCR_REG.TWSTO_pin = 0;
    TWCR_REG.TWEN_pin = 1;
    TWCR_REG.TWINT_pin = 1;
    
    while (!TWCR_REG.TWINT_pin);

    return TWSR_REG.TWS_pins != I2C_ByteTransmittedAckRecived ? TWSR_REG.TWS_pins : 0;
}

void I2C_stopCondition()
{
    TWCR_REG.TWSTA_pin = 0;
    TWCR_REG.TWSTO_pin = 1;
    TWCR_REG.TWEN_pin = 1;
    TWCR_REG.TWINT_pin = 1;
}

u8 I2C_masterTransmit(u8 slaveAddress, u8 *data, u8 dataLen) {
    u8 status, i;

    status = I2C_startCondition();
    if (status) {
        I2C_stopCondition();
        return status;
    }


    while (1) {
        status = I2C_masterWriteAdderss(slaveAddress);
        if (status == I2C_ArbitrationLost)
            continue;
        if (status) {
            I2C_stopCondition();
            return status;
        }

        for (i = 0; !status && i < dataLen; ++i) {
            status = I2C_writeByte(data[i]);
        }

        if (status == I2C_ArbitrationLost)
            continue;

        I2C_stopCondition();
        return status;
    }
}
