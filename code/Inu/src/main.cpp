
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "controller.h"
#include "kinematics.h"
#include "servo_controller.h"

SoftwareSerial ser(2, 3);

ControllerData data;

ServoController servo = ServoController();
Kinematics kinematics = Kinematics();

float fl_coords[3] = {0.0, 0.0, 100.0};
float fr_coords[3] = {0.0, 0.0, 100.0};

int fl_angles[3] = {90, 90, 90};
int fr_angles[3] = {90, 90, 90};

char message[50];

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    ser.begin(115200);

    servo.start();

    servo.move_servo(0, 90);
    servo.move_servo(1, 90);
    servo.move_servo(2, 90);
    Serial.flush();
}

void loop() {
    delay(10);

    if (Serial.available()) {
        Serial.readBytes((byte*)&data, sizeof(ControllerData));
    }

    if (data.mode == 1.0f) {
        fl_coords[0] = data.position[0];
        fl_coords[1] = data.position[1];
        fl_coords[2] = data.position[2];

        kinematics.single_leg_ik(fl_angles, fl_coords, 0.0, 0.0, true);

        servo.move_servo(0, fl_angles[0]);
        servo.move_servo(1, fl_angles[1]);
        servo.move_servo(2, fl_angles[2]);

        ser.print(fl_angles[0]);
        ser.print(" ");
        ser.print(fl_angles[1]);
        ser.print(" ");
        ser.println(fl_angles[2]);
    }
}