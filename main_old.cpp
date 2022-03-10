
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "controller.h"
#include "kinematics.h"
#include "servo_controller.h"

SoftwareSerial ser(2, 3);

ControllerData data;

ServoController servo = ServoController();
Kinematics kinematics = Kinematics();

float fl_pos[3] = {0.0, 0.0, 100.0};
float fr_pos[3] = {0.0, 0.0, 100.0};

int fl_angles[3] = {90, 90, 90};
int fr_angles[3] = {90, 90, 90};

unsigned long currentMillis;
unsigned long prevMillis = 0;
unsigned long interval = 10;

unsigned long simpleInterval = 500;
unsigned long prevStepMills = 0;
unsigned int simpleStep = 0;

unsigned long remoteMillis = 0;

void setup() {
    Serial.begin(115200);
    ser.begin(115200);

    servo.start();

    data.position[0] = 0;
    data.position[1] = 0;
    data.position[2] = 141;

    data.rotation[0] = 0;
    data.rotation[1] = 0;
    data.rotation[2] = 0;

    // kinematics.single_leg_ik(fl_angles, data.position, data.rotation, 0.0, 0.0, true);

    servo.move_servo(0, fl_angles[0]);
    servo.move_servo(1, fl_angles[1]);
    servo.move_servo(2, constrain(fl_angles[2], 0, 170));

    servo.move_servo(4, fr_angles[0]);
    servo.move_servo(5, fr_angles[1]);
    servo.move_servo(6, constrain(fr_angles[2], 10, 180));

    Serial.flush();
}

void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis >= interval) {
        prevMillis = currentMillis;

        if (Serial.available()) {
            Serial.readBytes((byte*)&data, sizeof(ControllerData));
        }

        if (data.mode == 0.0) {
            data.position[0] = 0;
            data.position[1] = 0;
            data.position[2] = 141;

            data.rotation[0] = 0;
            data.rotation[1] = 0;
            data.rotation[2] = 141;

            kinematics.single_leg_ik(fl_angles, data.position, data.rotation, 0.0, 0.0, true);
            kinematics.single_leg_ik(fr_angles, data.position, data.rotation, 0.0, 0.0, false);

            servo.move_servo(0, fl_angles[0]);
            servo.move_servo(1, fl_angles[1]);
            servo.move_servo(2, constrain(fl_angles[2], 0, 170));

            servo.move_servo(4, fr_angles[0]);
            servo.move_servo(5, fr_angles[1]);
            servo.move_servo(6, constrain(fr_angles[2], 10, 180));
        }

        if (data.mode == 1.0) {
            kinematics.single_leg_ik(fl_angles, data.position, data.rotation, 0.0, 0.0, true);
            kinematics.single_leg_ik(fr_angles, data.position, data.rotation, 0.0, 0.0, false);

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
            ser.println();

        } else if (data.mode == 2.0) {
            if (simpleStep == 0 && currentMillis - prevStepMills > simpleInterval) {
                fl_pos[0] = 100;
                fl_pos[1] = 0;
                fl_pos[2] = 160;

                fr_pos[0] = -100;
                fr_pos[1] = 0;
                fr_pos[2] = 141;

                simpleStep = 1;
                prevStepMills = currentMillis;
            } else if (simpleStep == 1 && currentMillis - prevStepMills > simpleInterval) {
                fl_pos[0] = -100;
                fl_pos[1] = 0;
                fl_pos[2] = 141;

                fr_pos[0] = 100;
                fr_pos[1] = 0;
                fr_pos[2] = 160;

                simpleStep = 0;
                prevStepMills = currentMillis;
            }

            ser.println(simpleStep);

            kinematics.single_leg_ik(fl_angles, fl_pos, data.rotation, 0.0, 0.0, true);
            kinematics.single_leg_ik(fr_angles, fr_pos, data.rotation, 0.0, 0.0, false);

            servo.move_servo(0, fl_angles[0]);
            servo.move_servo(1, fl_angles[1]);
            servo.move_servo(2, constrain(fl_angles[2], 0, 170));

            servo.move_servo(4, fr_angles[0]);
            servo.move_servo(5, fr_angles[1]);
            servo.move_servo(6, constrain(fr_angles[2], 10, 180));
        }
    }
}