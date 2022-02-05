
#include <Arduino.h>

#include "kinematics.h"
#include "servo_controller.h"

int angles[3] = {0, 0, 0};
float coords[3] = {0, 0, 141.421356237};

ServoController servo = ServoController();
Kinematics kinematics = Kinematics();

void setup() {
    Serial.begin(9600);

    servo.start();
    // kinematics.single_leg_ik(angles, coords);

    // Serial.println(angles[0]);
    // Serial.println(angles[1]);
    // Serial.println(angles[2]);

    // servo.move_servo(0, angles[0]);
    // servo.move_servo(1, angles[1]);
    // servo.move_servo(2, angles[2]);

    Serial.println("Inu Running...");
}

void loop() {
    // delay(10);

    // kinematics.single_leg_ik(angles, coords);

    // // Serial.println(coords[2]);
    // Serial.println(coords[0]);

    // servo.move_servo(0, angles[0]);
    // servo.move_servo(1, angles[1]);
    // servo.move_servo(2, angles[2]);

    // coords[0] += 1;

    // if (coords[0] > 100) {
    //     coords[0] = -100;
    // }

    // // coords[2] += 1;

    // // if (coords[2] > 200) {
    // //     coords[2] = 1;
    // // }
}