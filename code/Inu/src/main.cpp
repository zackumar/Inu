
#include <Arduino.h>

#include "servo_controller.h"

void setup() {
    Serial.begin(9600);
    Serial.println("Hello World!");

    ServoController servo;

    delay(100);

    servo.move_servo(0, 180);
}

void loop() {
    // put your main code here, to run repeatedly:
}