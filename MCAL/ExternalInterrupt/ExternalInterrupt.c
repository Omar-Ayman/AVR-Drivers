
#include "ExternalInterrupt_prv.h"

#include <VL/BitArithmetics.h>

static PinInfo INT_pinInfos[3] = {INT0_PIN_INFO, INT1_PIN_INFO, INT2_PIN_INFO};
static volatile u8 *ISC_regs[3] = {MCUCR_PTR, MCUCR_PTR, MCUCSR_PTR};
static u8 ISC_bits[3] = {2, 2, 1};
static u8 ISC_offsets[3] = {ISC00_PIN, ISC10_PIN, ISC2_PIN};
static u8 INT_pins[3] = {INT0_PIN, INT1_PIN, INT2_PIN};
static ExternalInterruptHandle handles[3] = {0, 0, 0};

ISR_HEAD(INT0_ISR_VCT) {
    if (handles[0])
        handles[0]();
}

ISR_HEAD(INT1_ISR_VCT) {
    if (handles[1])
        handles[1]();
}

ISR_HEAD(INT2_ISR_VCT) {
    if (handles[2])
        handles[2]();
}

void ExternalInterrupt_setupPin(PinInfo pin, ExternalInterrupt_Type type, ExternalInterruptHandle handle) {
    u8 i;
    for (i = 0; i < 3 && AS_U8(pin) != AS_U8(INT_pinInfos[i]); ++i);
    if (i == 3)
        return;

    DIO_setPinDirection(pin, INPUT);
    ASS_BITS(*ISC_regs[i], ISC_bits[i], ISC_offsets[i], type);
    SET_BIT(*GICR_PTR, INT_pins[i]);
    SREG_REG.I_pin = 1;
    handles[i] = handle;
}