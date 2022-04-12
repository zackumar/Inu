#include "servo_controller.h"

#include "pwm_controller.h"

ServoController::ServoController() {
}

void ServoController::start() {
    start(i2c0, 4, 5, 0x40);
}

void ServoController::start(i2c_inst_t* i2c, uint SDA, uint SCL, uint8_t i2c_address) {
    pwm = PWMController(i2c, SDA, SCL, i2c_address);
    pwm.begin();
}

long ServoController::pulseFromDegrees(int degrees) {
    return pwm.map(degrees, 0, 180, SERVOMIN, SERVOMAX);
}

void ServoController::moveServo(int servo_num, int degrees) {
    long pulselen = pulseFromDegrees(degrees);
    pwm.setPWM(servo_num, (int16_t)pulselen);
}