
#include "ADC_prv.h"
#include "ADC.h"

static u8 initializedADC = 0;

void ADC_initGeneral() {
    initializedADC = 1;
    ADCSRA_REG.ADEN_pin = 1;
    ADCSRA_REG.ADPS = ADC_Prescale128;
    ADMUX_REG.REFS = ADC_ReferenceAVCC;
    ADMUX_REG.ADLAR_pin = 0;
}

void ADC_init(PinInfo pin) {
    if (pin.port != PORTA_IDX)
        return;

    DIO_setPinDirectionInitVal(pin, INPUT, 0);
    if (!initializedADC)
        ADC_initGeneral();
}

u16 ADC_readValue(PinInfo pin) {
    if (pin.port != PORTA_IDX)
        return;

    ADMUX_REG.MUX = pin.pin;
    ADCSRA_REG.ADIF_pin = 0;
    ADCSRA_REG.ADSC_pin = 1;
    while (!ADCSRA_REG.ADIF_pin);
    ADCSRA_REG.ADIF_pin = 1;

    return ADC_REG;
}
u16 ADC_readMilliVolts(PinInfo pin) {
    return (((u32)ADC_readValue(pin)) * ADC_MAX_MV) / ADC_MAX_VALUE;
}
