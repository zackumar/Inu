
#include <Arduino.h>

#include "kinematics.h"
#include "servo_controller.h"

int left_angles[3] = {90, 90, 90};
int right_angles[3] = {90, 90, 90};
float coords[3] = {0, 0, 0};

ServoController servo = ServoController();
Kinematics kinematics = Kinematics();

const int x_pot_pin = A0;
const int y_pot_pin = A1;
const int z_pot_pin = A2;
int x_val = 0;
int y_val = 0;
int z_val = 0;

void setup() {
    pinMode(x_pot_pin, INPUT);
    pinMode(y_pot_pin, INPUT);
    pinMode(z_pot_pin, INPUT);

    Serial.begin(9600);

    servo.start();

    Serial.println("Inu Running...");
}

void loop() {
    x_val = analogRead(x_pot_pin);
    y_val = analogRead(y_pot_pin);
    z_val = analogRead(z_pot_pin);

    int x = map(x_val, 0, 1023, -150, 150);
    int y = map(y_val, 0, 1023, -100, 100);
    int z = map(z_val, 0, 1023, 1, 200);

    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);

    coords[0] = x;
    coords[1] = y;
    coords[2] = z;

    kinematics.single_leg_ik(left_angles, coords, 0, 0, true);
    kinematics.single_leg_ik(right_angles, coords, 0, 0, false);

    servo.move_servo(0, left_angles[0]);
    servo.move_servo(1, left_angles[1]);
    servo.move_servo(2, left_angles[2]);

    servo.move_servo(4, right_angles[0]);
    servo.move_servo(5, right_angles[1]);
    servo.move_servo(6, right_angles[2]);
}