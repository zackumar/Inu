#ifndef PWM_CONTROLLER_H
#define PWM_CONTROLLER_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "pwm_controller.h"

class PWMController {
   public:
    PWMController(i2c_inst_t* i2c, uint SDA, uint SCL, uint8_t i2c_address = 0x40);
    void begin(void);
    void setFreq(uint16_t freq);
    void setPWM(uint8_t channel, int16_t pwm);
    long map(long x, long in_min, long in_max, long out_min, long out_max);

    void regWrite(const uint8_t reg, uint8_t value);
    uint8_t regRead(const uint8_t reg);

   private:
    i2c_inst_t* _i2c;
    uint _SDA;
    uint _SCL;
    uint8_t _i2c_address;
};

#endif