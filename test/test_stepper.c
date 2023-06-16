
#include <HAL/Stepper/Stepper.h>
#include <VL/MCU.h>

Stepper stepper = {{{PORTC_IDX, PIN0_IDX}, {PORTC_IDX, PIN1_IDX}, {PORTC_IDX, PIN2_IDX}, {PORTC_IDX, PIN3_IDX}}, Stepper_HalfStepMode};

int main() {
    Stepper_init(&stepper);
    _delay_ms(1000);

    while (1) {
        // Stepper_moveSteps(&stepper, Stepper_Clockwise, 2000, STEPPER_MAX_FREQ);
        Stepper_moveAngle(&stepper, 180);
        _delay_ms(1000);
        // Stepper_moveSteps(&stepper, Stepper_CounterClockwise, 2000, STEPPER_MAX_FREQ);
        Stepper_moveAngle(&stepper, -180);
        _delay_ms(1000);
    }

    return 0;
}
