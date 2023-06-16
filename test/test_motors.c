
#include <HAL/DCMotor/DCMotor.h>

DCMotor dc = {{PORTD_IDX, PIN0_IDX}, {PORTD_IDX, PIN1_IDX}};

int main() {
    DCMotor_init(&dc);

    while (1) {
        
        DCMotor_rotateClockwise(&dc);
        _delay_ms(5000);
        DCMotor_rotateCounterClockwise(&dc);
        _delay_ms(5000);
        DCMotor_stop(&dc);
        _delay_ms(5000);
    }

    return 0;
}
