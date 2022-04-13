#include <stdio.h>

#include "controller.h"
#include "hardware/uart.h"
#include "kinematics.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "servo_controller.h"

#define UART_ID uart0
#define BAUDRATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

ControllerData data;

ServoController servo;
Kinematics kinematics;

float flPos[3] = {0.0, 0.0, 100.0};
float frPos[3] = {0.0, 0.0, 100.0};

int flAngles[3] = {90, 90, 90};
int frAngles[3] = {90, 90, 90};

uint32_t currentMillis;
uint32_t prevMillis = 0;
uint32_t interval = 10;

char out[50];

void setup() {
    uart_init(UART_ID, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    uart_puts(UART_ID, "Hello world");

    servo.start();

    data.position[0] = 0;
    data.position[1] = 0;
    data.position[2] = 141;

    data.rotation[0] = 0;
    data.rotation[1] = 0;
    data.rotation[2] = 0;

    servo.moveServo(0, flAngles[0]);
    servo.moveServo(1, flAngles[1]);
    servo.moveServo(2, flAngles[2]);

    servo.moveServo(4, frAngles[0]);
    servo.moveServo(5, frAngles[1]);
    servo.moveServo(6, frAngles[2]);
}

void loop() {
    currentMillis = to_ms_since_boot(get_absolute_time());
    if (currentMillis - prevMillis >= interval) {
        prevMillis = currentMillis;

        if (uart_is_readable(UART_ID)) {
            uart_read_blocking(UART_ID, (uint8_t*)&data, sizeof(ControllerData));
        }

        if (data.mode == 1.0) {
            kinematics.singleLegIK(flAngles, data.position, data.rotation, 0.0, 0.0, true);
            kinematics.singleLegIK(frAngles, data.position, data.rotation, 0.0, 0.0, false);

            servo.moveServo(0, flAngles[0]);
            servo.moveServo(1, flAngles[1]);
            servo.moveServo(2, constrain(flAngles[2], 10, 170));

            servo.moveServo(4, frAngles[0]);
            servo.moveServo(5, frAngles[1]);
            servo.moveServo(6, constrain(frAngles[2], 10, 170));

            sprintf(out, "W: %d, E: %d, S: %d\n", flAngles[0], flAngles[2], flAngles[3]);

            uart_puts(UART_ID, out);
        }
    }
}

int main() {
    setup();

    while (1) {
        loop();
    }
}
