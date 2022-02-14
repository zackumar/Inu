
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

unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long interval = 10;

char message[50];

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    ser.begin(115200);

    servo.start();

    servo.move_servo(0, fl_angles[0]);
    servo.move_servo(1, fl_angles[1]);
    servo.move_servo(2, fl_angles[2]);

    servo.move_servo(4, fr_angles[0]);
    servo.move_servo(5, fr_angles[1]);
    servo.move_servo(6, fr_angles[2]);

    Serial.flush();
}

void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis >= interval) {
        prevMillis = currentMillis;

        if (Serial.available()) {
            Serial.readBytes((byte*)&data, sizeof(ControllerData));
        }

        if (data.mode == 1.0) {
            kinematics.single_leg_ik(fl_angles, data.position, 0.0, 0.0, true);
            kinematics.single_leg_ik(fr_angles, data.position, 0.0, 0.0, false);

            servo.move_servo(0, fl_angles[0]);
            servo.move_servo(1, fl_angles[1]);
            servo.move_servo(2, constrain(fl_angles[2], 0, 170));

            servo.move_servo(4, fr_angles[0]);
            servo.move_servo(5, fr_angles[1]);
            servo.move_servo(6, constrain(fr_angles[2], 10, 180));

            ser.print("Left - W: ");
            ser.print(fl_angles[0]);
            ser.print(" E: ");
            ser.print(fl_angles[1]);
            ser.print(" S: ");
            ser.print(fl_angles[2]);
            // ser.print(" | Right - W: ");
            // ser.print(fr_angles[0]);
            // ser.print(" E: ");
            // ser.print(fr_angles[1]);
            // ser.print(" S: ");
            // ser.print(fr_angles[2]);
            ser.println();
        }
    }
}