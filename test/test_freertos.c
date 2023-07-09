
#include <VL/MCU.h>
#include <MCAL/DIO/DIO.h>
#include <MCAL/ExternalInterrupt/ExternalInterrupt.h>

#include <FreeRTOS/FreeRTOS.h>
#include <FreeRTOS/task.h>
#include <FreeRTOS/semphr.h>

PinInfo led = {PORTC_IDX, PIN0_IDX};
PinInfo button = INT0_PIN_INFO;

BaseType_t temp;
SemaphoreHandle_t sem;

void buttonIsr() {
    xSemaphoreGiveFromISR(sem, &temp);
}

// void buttonFn(void *params) {
//     TickType_t upTime = xTaskGetTickCount();
//     u8 prevStatus = 1, status;
//     while (1) {
//         status = DIO_readPin(button);
//         if (status != prevStatus) {
//             prevStatus = status;
//             xSemaphoreGive(sem);
//         }
//         xTaskDelayUntil(&upTime, unitDelay);
//     }
// }

void ledFn(void *params) {
    while (1) {
        if (xSemaphoreTake(sem, portMAX_DELAY) == pdPASS);
            DIO_togglePin(led);
    }
}

int main() {
    sem = xSemaphoreCreateBinary();

    ExternalInterrupt_setupPin(button, ExternalInterrupt_onChange, buttonIsr);
    DIO_setPinDirection(led, OUTPUT);
    // DIO_setPinDirection(button, INPUT);

    xTaskCreate(ledFn, "ledTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // xTaskCreate(buttonFn, "btnTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);
    return 1;
}
