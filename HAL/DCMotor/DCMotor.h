
#ifndef _DC_MOTOR_H
#define _DC_MOTOR_H

#include <MCAL/DIO/DIO.h>
#include <VL/MCU.h>

typedef struct DCMotor {
    PinInfo enA;
    PinInfo enB;
} DCMotor;

void DCMotor_init(DCMotor *motor);

void DCMotor_stop(DCMotor *motor);

void DCMotor_rotateClockwise(DCMotor *motor);

void DCMotor_rotateCounterClockwise(DCMotor *motor);

#endif