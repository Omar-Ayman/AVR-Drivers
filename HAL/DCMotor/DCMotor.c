
#include "DCMotor.h"

void DCMotor_init(DCMotor *motor) {
    DIO_setPinDirection(motor->enA, OUTPUT);
    DIO_setPinDirection(motor->enB, OUTPUT);
    DCMotor_stop(motor);
}

void DCMotor_stop(DCMotor *motor) {
    DIO_writePin(motor->enA, LOW);
    DIO_writePin(motor->enB, LOW);
}

void DCMotor_rotateClockwise(DCMotor *motor) {
    DIO_writePin(motor->enA, HIGH);
    DIO_writePin(motor->enB, LOW);
}

void DCMotor_rotateCounterClockwise(DCMotor *motor) {
    DIO_writePin(motor->enA, LOW);
    DIO_writePin(motor->enB, HIGH);
}
