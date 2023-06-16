
#ifndef _STEPPER_H
#define _STEPPER_H

#include <MCAL/DIO/DIO.h>

#define STEPPER_MAX_FREQ 100

typedef ENUM_PACKED Stepper_Mode {
    Stepper_FullStepMode = 0,
    Stepper_HalfStepMode = 1
} Stepper_Mode;

typedef ENUM_PACKED Stepper_Direction {
    Stepper_Clockwise = 0,
    Stepper_CounterClockwise = 1
} Stepper_Direction;

typedef struct Stepper {
    PinInfo coils[4];
    Stepper_Mode mode;

    u8 coilStatus[4];
    u8 currentCoilIdx;
} Stepper;

void Stepper_init(Stepper *stepper);

void Stepper_stepOnce(Stepper *stepper, Stepper_Direction direction);

void Stepper_moveSteps(Stepper *stepper, Stepper_Direction direction, u32 steps, u8 frequency);

void Stepper_moveAngle(Stepper *stepper, f32 angle);

#endif