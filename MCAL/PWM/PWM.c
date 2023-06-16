
#include "PWM_prv.h"
#include "PWM.h"

#include <VL/MCU.h>
#include <VL/BitArithmetics.h>

#include <VL/math.h>

static const PinInfo OC0PinInfo = OC0_PIN_INFO;
static const PinInfo OC1APinInfo = OC1A_PIN_INFO;
static const PinInfo OC1BPinInfo = OC1B_PIN_INFO;
static const PinInfo OC2PinInfo = OC2_PIN_INFO;

static const u8 prescalerSelect[] = {0b001, 0b010, 0b010, 0b010, 0b011, 0b011, 0b011, 0b100, 0b100, 0b101, 0b101};
static const u16 prescalerExponent[] = {0, 3, 6, 8, 10};

static volatile struct TCCRx_RegStruct *TCCRx_REGS[] = {TCCR0_PTR, TCCR2_PTR};
static volatile u8 *TCCRx_PTRS[] = {TCCR0_RAW, TCCR2_RAW};
// static volatile u8 *TCNTx_REGS[] = {TCNT0_PTR, TCNT2_PTR};
static volatile u8 *OCRx_REGS[] = {OCR0_PTR, OCR2_PTR};

#define PWM_8BIT_IDX(PI) (PI.port >> 1)


static const u8 COM1a_pinsOffset[] = {4, 6};
static const u8 OCIE1a_pinOffset[] = {3, 4};
static volatile u16 *OCR1a_REGS[] = {OCR1B_PTR, OCR1A_PTR};

#define PWM_16BIT_IDX(PI) (PI.pin & 1)

static u16 totalCustomValues[2] = {0, 0};
static u16 limitCustomValues[2][2] = {{77, 77}, {0, 0}};
static PinInfo customPWMPins[2];
static volatile u8 timerStates[2] = {0, 0};
static volatile u16 temp;

ISR_HNDL(TMR0_OVFL_ISR_VCT) {
    timerStates[0] ^= 1;
    temp = limitCustomValues[0][timerStates[0]];
    if (temp != 0xff) {
        *TCNT0_PTR = temp;
        DIO_writePin(customPWMPins[0], timerStates[0]);
    }
}

ISR_HNDL(TMR2_OVFL_ISR_VCT) {
    timerStates[1] ^= 1;
    temp = limitCustomValues[1][timerStates[1]];
    if (temp != 0xff) {
        *TCNT2_PTR = temp;
        DIO_writePin(customPWMPins[1], timerStates[1]);
    }
}

void PWM_initDefault(PinInfo pin) {
    u8 i;

    if ((pin.pin == OC0PinInfo.pin && pin.port == OC0PinInfo.port) || (pin.pin == OC2PinInfo.pin && pin.port == OC2PinInfo.port)) {

        DIO_setPinDirection(pin, OUTPUT);
        i = PWM_8BIT_IDX(pin);

        TCCRx_REGS[i]->WGMx0_pin = 1;
        TCCRx_REGS[i]->WGMx1_pin = 0;
        TCCRx_REGS[i]->COMx_pins = 0b10;
        TCCRx_REGS[i]->CSx_pins = 0b001;
        CLR_BIT(TIMSK_RAW,     i * 6);
        CLR_BIT(TIMSK_RAW, 1 + i * 6);
        *OCRx_REGS[i] = 0;
        // *TCNTx_REGS[i] = 0;

    } else if ((pin.pin == OC1APinInfo.pin && pin.port == OC1APinInfo.port) || (pin.pin == OC1BPinInfo.pin && pin.port == OC1BPinInfo.port)) {

        DIO_setPinDirection(pin, OUTPUT);
        i = PWM_16BIT_IDX(pin);

        TCCR1A_REG.WGM1L_pins = 0b11;
        TCCR1B_REG.WGM1H_pins = 0b00;
        ASS_BITS(TCCR1A_RAW, 2, COM1a_pinsOffset[i], 0b10);
        TCCR1B_REG.CS1_pins = 0b001;
        TIMSK_REG.OCIE1A_pin = 0;
        TIMSK_REG.TOIE1_pin = 0;
        TIMSK_REG.TICIE1_pin = 0;
        *OCR1a_REGS[i] = 0;
        // TCNT1_REG = 0;

    }
}

void PWM_initCustomFreq(PinInfo pin, u32 fr) {
    u8 i, mult, ps;
    u64 top;

    if ((pin.pin == OC1APinInfo.pin && pin.port == OC1APinInfo.port) || (pin.pin == OC1BPinInfo.pin && pin.port == OC1BPinInfo.port)) {

        DIO_setPinDirection(pin, OUTPUT);
        i = PWM_16BIT_IDX(pin);

        TCCR1A_REG.WGM1L_pins = 0b10;
        TCCR1B_REG.WGM1H_pins = 0b10;
        ASS_BITS(TCCR1A_RAW, 2, COM1a_pinsOffset[i], 0b10);
        TIMSK_REG.OCIE1A_pin = 0;
        TIMSK_REG.TOIE1_pin = 0;
        TIMSK_REG.TICIE1_pin = 0;

        top = ((u64)F_CPU) / (fr * 2);
        mult = int_log_2(top >> 16) + ((top & 0xffff) != 0);
        ps = prescalerSelect[mult];
        TCCR1B_REG.CS1_pins = ps;
        ICR1_REG = top >> prescalerExponent[ps - 1];
        
        *OCR1a_REGS[i] = 0;
        TCNT1_REG = 0;

    }
}

void PWM_writeDutyCycle(PinInfo pin, u16 dutyCycle) {
    if ((pin.pin == OC0PinInfo.pin && pin.port == OC0PinInfo.port) || (pin.pin == OC2PinInfo.pin && pin.port == OC2PinInfo.port)) {

        *OCRx_REGS[PWM_8BIT_IDX(pin)] = 0xff * ((u32)dutyCycle) / PWM_MAX_DUTY_CYCLE;

    } else if ((pin.pin == OC1APinInfo.pin && pin.port == OC1APinInfo.port) || (pin.pin == OC1BPinInfo.pin && pin.port == OC1BPinInfo.port)) {

        *OCR1a_REGS[PWM_16BIT_IDX(pin)] = (TCCR1B_REG.WGM1H_pins ? ICR1_REG : 0x3ff) * ((u32)dutyCycle) / PWM_MAX_DUTY_CYCLE;

    }
}

void PWM_writeVolts(PinInfo pin, u16 milliVolt) {
    // if (volt > PWM_MAX_VOLT)
    //     volt = PWM_MAX_VOLT;

    // volt = volt / PWM_MAX_VOLT;
    // volt *= volt;

    PWM_writeDutyCycle(pin, milliVolt * PWM_MAX_DUTY_CYCLE / PWM_MAX_MV);
}

PWMCustomHandle PWMCustom_init(PinInfo pin, u32 fr) {
    u8 i, mult, ps, topVal;
    u64 top;

    if (!*TCCRx_PTRS[0]) {
        i = 0;
    } else if (!*TCCRx_PTRS[1]) {
        i = 1;
    } else {
        return 0xff;
    }

    customPWMPins[i] = pin;
    DIO_setPinDirection(pin, OUTPUT);

    if (fr) {
        top = F_CPU / fr;
        mult = int_log_2(top >> 8) + ((top & 0xff) != 0);
        if (mult > 10) mult = 10;
        ps = prescalerSelect[mult];
        topVal = (top >> prescalerExponent[ps - 1]) - 2;
        if (!topVal) topVal = 0xff;
    } else {
        ps = 0b001;
        topVal = 0xff;
    }

    TCCRx_REGS[i]->CSx_pins = ps;
    totalCustomValues[i] = topVal;
    // limitCustomValues[i][0] = 0xff - topVal;
    // *TCCRx_PTRS[i] = ps;
    
    TCCRx_REGS[i]->WGMx0_pin = 0;
    TCCRx_REGS[i]->WGMx1_pin = 0;
    TCCRx_REGS[i]->COMx_pins = 0b00;

    TCCRx_REGS[i]->COMx_pins = 0b00;
    // PWMCustom_writeDutyCycle(i, PWM_MAX_DUTY_CYCLE >> 1);
    // TIMSK_REG.TOIE0_pin = 1;
    SET_BIT(TIMSK_RAW,     i * 6);
    CLR_BIT(TIMSK_RAW, 1 + i * 6);
    SREG_REG.I_pin = 1;

    return i;
}

void PWMCustom_writeDutyCycle(PWMCustomHandle handle, u8 dutyCycle) {
    u8 value;
    // if (dutyCycle > 1) dutyCycle = 1;
    totalCustomValues[handle] = 154;
    value = totalCustomValues[handle] * dutyCycle / PWM_MAX_DUTY_CYCLE;

    // CLR_BIT(TIMSK_RAW, handle * 6);
    limitCustomValues[handle][1] = 0xff - value;
    limitCustomValues[handle][0] = 0xff - (totalCustomValues[handle] - value);
    // SET_BIT(TIMSK_RAW, handle * 6);
}

void PWMCustom_writeVolts(PWMCustomHandle handle, u16 milliVolt) {
    PWMCustom_writeDutyCycle(handle, milliVolt * PWM_MAX_DUTY_CYCLE / PWM_MAX_MV);
}
