
#include "Stepper.h"

#include <VL/MCU.h>
#include <math.h>

#define STEPPER_ANGLE_PER_STEP 0.17578125

static float freqMult[] = { 2, 1 };

void Stepper_init(Stepper *stepper) {
    u8 i;
    
    stepper->currentCoilIdx = 0;
    stepper->coilStatus[i] = HIGH;
    for (i = 1; i < 4; ++i)
        stepper->coilStatus[i] = LOW;

    for (i = 0; i < 4; ++i) {
        DIO_setPinDirection(stepper->coils[i], OUTPUT);
        DIO_writePin(stepper->coils[i], stepper->coilStatus[i]);
    }
}

void Stepper_stepOnce(Stepper *stepper, Stepper_Direction direction) {
    u8 nextCoilIdx, prevCoilIdx;

    if (direction == Stepper_Clockwise) {
        nextCoilIdx = (stepper->currentCoilIdx + 3) % 4;
        prevCoilIdx = (stepper->currentCoilIdx + 1) % 4;
    } else if (direction == Stepper_CounterClockwise) {
        nextCoilIdx = (stepper->currentCoilIdx + 1) % 4;
        prevCoilIdx = (stepper->currentCoilIdx + 3) % 4;
    } else return;
    
    switch (stepper->mode) {
        case Stepper_FullStepMode:
            stepper->coilStatus[nextCoilIdx] = HIGH;
            DIO_writePin(stepper->coils[nextCoilIdx], HIGH);
            stepper->coilStatus[stepper->currentCoilIdx] = LOW;
            DIO_writePin(stepper->coils[stepper->currentCoilIdx], LOW);
            stepper->currentCoilIdx = nextCoilIdx;
            break;

        case Stepper_HalfStepMode:
            if (stepper->coilStatus[prevCoilIdx] == HIGH) {
                stepper->coilStatus[prevCoilIdx] = LOW;
                DIO_writePin(stepper->coils[prevCoilIdx], LOW);
            } else if (stepper->coilStatus[nextCoilIdx] == HIGH) {
                stepper->coilStatus[stepper->currentCoilIdx] = LOW;
                DIO_writePin(stepper->coils[stepper->currentCoilIdx], LOW);
                stepper->currentCoilIdx = nextCoilIdx;
            } else {
                stepper->coilStatus[nextCoilIdx] = HIGH;
                DIO_writePin(stepper->coils[nextCoilIdx], HIGH);
            }
            break;
    }
}

void Stepper_moveSteps(Stepper *stepper, Stepper_Direction direction, u32 steps, u8 frequency) {
    u32 s;
    u16 t;

    if (frequency > STEPPER_MAX_FREQ)
        frequency = STEPPER_MAX_FREQ;
    
    t = 1000 / frequency;

    for (s = 0; s < steps; ++s) {
        Stepper_stepOnce(stepper, direction);
        _delay_ms(t);
    }
}

void Stepper_moveAngle(Stepper *stepper, f32 angle) {
    Stepper_moveSteps(stepper, angle >= 0 ? Stepper_CounterClockwise : Stepper_Clockwise, fabsf(angle) * (stepper->mode + 1) / STEPPER_ANGLE_PER_STEP, STEPPER_MAX_FREQ);
}
