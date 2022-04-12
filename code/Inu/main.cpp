#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "servo_controller.h"

int main() {
    ServoController servo;

    servo.start();
    servo.moveServo(0, 0);
}