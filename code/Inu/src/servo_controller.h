#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define SERVOMIN 150
#define SERVOMAX 600
#define SERVO_FREQ 50

class ServoController {
   private:
    Adafruit_PWMServoDriver pwm;
    long pulse_from_degrees(int degrees);

   public:
    ServoController();

    /**
     * @brief Move servo to position in degrees
     *
     * @param servo_num Servo index starting from 0
     * @param degrees Degrees from 0-180
     */
    void move_servo(int servo_num, int degrees);
};

#endif