#include <stdio.h>

#include "controller.h"
#include "hardware/uart.h"
#include "kinematics.h"
#include "pico/stdlib.h"
#include "servo_controller.h"

#define UART_ID uart0
#define BAUDRATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

ControllerData data;

ServoController servo;
Kinematics kinematics;

float flPos[3] = {0.0, 0.0, 100.0};
float frPos[3] = {0.0, 0.0, 100.0};

int flAngles[3] = {90, 90, 90};
int frAngles[3] = {90, 90, 90};

unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long interval = 10;

int16_t constrain(int16_t x, int16_t max, int16_t min) {
    if (x > max) return max;
    if (x < min) return min;
    return x;
}

void setup() {
    uart_init(UART_ID, BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

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

// void loop() {
//     currentMillis = millis();
//     if (currentMillis - prevMillis >= interval) {
//         prevMillis = currentMillis;

//         if (Serial.available()) {
//             Serial.readBytes((byte*)&data, sizeof(ControllerData));
//         }

//         if (data.mode == 1.0) {
//             kinematics.single_leg_ik(flAngles, data.position, data.rotation, 0.0, 0.0, true);
//             kinematics.single_leg_ik(frAngles, data.position, data.rotation, 0.0, 0.0, false);

//             servo.move_servo(0, flAngles[0]);
//             servo.move_servo(1, flAngles[1]);
//             servo.move_servo(2, constrain(flAngles[2], 0, 170));

//             servo.move_servo(4, frAngles[0]);
//             servo.move_servo(5, frAngles[1]);
//             servo.move_servo(6, constrain(frAngles[2], 10, 180));

//             ser.print("Left - W: ");
//             ser.print(flAngles[0]);
//             ser.print(" E: ");
//             ser.print(flAngles[1]);
//             ser.print(" S: ");
//             ser.print(flAngles[2]);
//             ser.println();
//         }
//     }
// }

int main() {
    setup();
}
