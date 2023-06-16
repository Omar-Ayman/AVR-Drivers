
#include <VL/MCU.h>

#include <MCAL/PWM/PWM.h>
#include <MCAL/ADC/ADC.h>
// #include <HAL/LCD/LCD.h>
#include <HAL/SevenSegment/SevenSegment.h>
// #include <HAL/DCMotor/DCMotor.h>
#include <MCAL/UART/UART.h>

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/task.h>
#include <FreeRTOS/timers.h>

#include "TransmitData.h"

// resources

PinInfo pwmPin = {PORTD_IDX, PIN6_IDX};
// LCD lcd = {{PORTC_IDX, 4, PIN4_IDX}, {PORTC_IDX, PIN0_IDX}, {PORTC_IDX, PIN1_IDX}, {PORTC_IDX, PIN2_IDX}};
SevenSegment sevseg = {{PORTC_IDX}, SevenSegment_CommonAnode};
// DCMotor motor = {{PORTD_IDX, PIN2_IDX}, {PORTD_IDX, PIN3_IDX}};
PinInfo enA = {PORTD_IDX, PIN2_IDX};
PinInfo enB = {PORTD_IDX, PIN3_IDX};

PWMCustomHandle pwmHandle;
u8 cursorPos = 0;
u8 motorLastState = 0;
TransmitData data = {0, 0, 0};

// interrupt handles

// task handles

void Task_PWM(void *params) {
    portTickType wakeTimePWM = xTaskGetTickCount();

    while (1) {
        PWMCustom_writeDutyCycle(pwmHandle, ((u32)data.adcVal) * 255 / ADC_MAX_VALUE / 20 + 13);
        vTaskDelayUntil(&wakeTimePWM, 50 / portTICK_RATE_MS);
    }
}

void Task_LCD(void *params) {
    portTickType wakeTimeLCD = xTaskGetTickCount();
    
    while (1) {
        if (data.keyPressed) {
            SevenSegment_writeDigit(&sevseg, data.keyPressed - 1);
            // if (data.keyPressed == '\b') {
            //     LCD_setCursorPos(&lcd, cursorPos--, 0);
            //     LCD_writeChar(&lcd, ' ');
            //     LCD_setCursorPos(&lcd, cursorPos, 0);
            // } else if (data.keyPressed == 'c') {
            //     LCD_clearDisplay(&lcd);
            //     LCD_resetCursor(&lcd);
            // } else if (cursorPos < 16) {
            //     LCD_writeChar(&lcd, data.keyPressed);
            // }
            // data.keyPressed = 0;
        } else {
            SevenSegment_clear(&sevseg);
        }
        vTaskDelayUntil(&wakeTimeLCD, 50 / portTICK_RATE_MS);
    }
}

void Task_Motor(void *params) {
    portTickType wakeTimeMotor = xTaskGetTickCount();

    while (1) {
        DIO_writePin(enA, data.intState0);
        DIO_writePin(enB, data.intState1);
        // if (motorLastState != data.intState) {
        //     motorLastState = data.intState;
        //     if (motorLastState == 1) {
        //         DCMotor_rotateClockwise(&motor);
        //     } else if (motorLastState == 2) {
        //         DCMotor_rotateCounterClockwise(&motor);
        //     } else {
        //         DCMotor_stop(&motor);
        //     }
        // }
        vTaskDelayUntil(&wakeTimeMotor, 50 / portTICK_RATE_MS);
    }
}

void Task_UART(void *params) {
    portTickType wakeTimeUART = xTaskGetTickCount();

    while (1) {
        UART_readBytes((u8*)&data, sizeof(data));
        vTaskDelayUntil(&wakeTimeUART, 50 / portTICK_RATE_MS);
    }
}

int main() {
    pwmHandle = PWMCustom_init(pwmPin, 50);
    // DCMotor_init(&motor);
    DIO_setPinDirection(enA, OUTPUT);
    DIO_setPinDirection(enB, OUTPUT);
    // LCD_init(&lcd);
    SevenSegment_init(&sevseg);
    UART_initCustom(UART_BAUD_RATE_DEFAULT, UART_ReciveOnly, UART_PARITY_DEFAULT, UART_DATA_LENGTH_DEFAULT, UART_STOP_BITS_DEFAULT);
    
    xTaskCreate(Task_PWM, "Task_PWM", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_LCD, "Task_LCD", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_Motor, "Task_Motor", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_UART, "Task_UART", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);

    return 0;
}
