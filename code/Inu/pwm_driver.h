#ifndef PWM_DRIVER_H
#define PWM_DRIVER_H

#include <stdint.h>

#define PCA9685_MODE1 0x00

class PWMDriver {
   public:
    PWMDriver();

    void begin();
    void reset();
    void sleep();
    void wakeup();

    void setPWMFreq(float freq);
    void setPWM(uint8_t num, uint16_t on, uint16_t off);
    void setOscillatorFrequency(uint32_t freq);

   private:
    uint8_t i2caddrl;
    uint32_t occillator_freq;

    uint8_t read8(uint8_t addr);
    void write8(uint8_t addr, uint8_t data);
};

#endif