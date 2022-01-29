#include "servo_controller.h"

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

ServoController::ServoController() {
    Serial.println("Servo Controller Started...");
    pwm = Adafruit_PWMServoDriver();
    pwm.begin();
    pwm.setPWMFreq(SERVO_FREQ);
}

long ServoController::pulse_from_degrees(int degrees) {
    return map(degrees, 0, 180, SERVOMIN, SERVOMAX);
}

void ServoController::move_servo(int servo_num, int degrees) {
    long pulselen = pulse_from_degrees(degrees);
    pwm.setPWM(servo_num, 0, pulselen);
}