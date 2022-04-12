#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pwm_controller.h"

int main() {
    PWMController servo(i2c0, 0, 1, 0x40);

    servo.begin();
    servo.setPWM(0, servo.map(90, 0, 180, 153, 557));
}