
#include <VL/MCU.h>
#include <VL/BitArithmetics.h>

#include <HAL/Keypad/Keypad.h>
#include <MCAL/ADC/ADC.h>
#include <MCAL/ExternalInterrupt/ExternalInterrupt.h>
#include <MCAL/UART/UART.h>

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/task.h>
#include <FreeRTOS/timers.h>

#include "TransmitData.h"

// resources

static const char keys[] = {
    '1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '\0', '0', '\0'
};

PinInfo adcPin = {PORTA_IDX, PIN0_IDX};
Keypad keypad = {{PORTB_IDX, 4, PIN0_IDX}, {PORTB_IDX, 3, PIN4_IDX}, keys};
PinInfo statePin0 = INT0_PIN_INFO;
PinInfo statePin1 = INT1_PIN_INFO;

TransmitData data = {0, 0, 0};
u8 tempKey;

// interrupt handles

void Interrupt0() {
    data.intState0 = !DIO_readPin(statePin0);
}

void Interrupt1() {
    data.intState1 = !DIO_readPin(statePin1);
}

// task handles

void Task_ADC(void *params) {
    portTickType wakeTimeADC = xTaskGetTickCount();

    while (1) {
        data.adcVal = ADC_readValue(adcPin);
        vTaskDelayUntil(&wakeTimeADC, 50 / portTICK_RATE_MS);
    }
}

void Task_KEY(void *params) {
    portTickType wakeTimeADC = xTaskGetTickCount();
    
    while (1) {
        tempKey = Keypad_getFirstPressedKey(&keypad);
        data.keyPressed = tempKey ? tempKey - '0' + 1 : 0;
        vTaskDelayUntil(&wakeTimeADC, 50 / portTICK_RATE_MS);
    }
}

void Task_UART(void *params) {
    portTickType wakeTimeUART = xTaskGetTickCount();

    while (1) {
        UART_writeBytes((u8*)&data, sizeof(data));
        vTaskDelayUntil(&wakeTimeUART, 50 / portTICK_RATE_MS);
    }
}

int main() {
    ADC_init(adcPin);
    ExternalInterrupt_setupPin(statePin0, ExternalInterrupt_onChange, Interrupt0);
    ExternalInterrupt_setupPin(statePin1, ExternalInterrupt_onChange, Interrupt1);
    Keypad_init(&keypad);
    UART_initCustom(UART_BAUD_RATE_DEFAULT, UART_TransmitOnly, UART_PARITY_DEFAULT, UART_DATA_LENGTH_DEFAULT, UART_STOP_BITS_DEFAULT);
    
    xTaskCreate(Task_ADC, "Task_ADC", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_KEY, "Task_Keypad", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_UART, "Task_UART", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);

    return 0;
}
