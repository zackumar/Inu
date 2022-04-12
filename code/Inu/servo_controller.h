#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include "pwm_controller.h"

#define SERVOMIN 153
#define SERVOMAX 557
#define SERVO_FREQ 50

class ServoController {
   private:
    PWMController pwm;
    long pulseFromDegrees(int degrees);

   public:
    ServoController();
    void start();
    void start(i2c_inst_t* i2c, uint SDA, uint SCL, uint8_t i2c_address);

    /**
     * @brief Move servo to position in degrees
     *
     * @param servo_num Servo index starting from 0
     * @param degrees Degrees from 0-180
     */
    void moveServo(int servo_num, int degrees);
};

#endif