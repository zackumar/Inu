#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "servo_controller.h"

PWMController::PWMController() {
}

PWMController::PWMController(i2c_inst_t* i2c, uint SDA, uint SCL, uint8_t i2c_address) {
    _i2c = i2c;
    _SDA = SDA;
    _SCL = SCL;
    _i2c_address = i2c_address;
}

void PWMController::begin(void) {
    i2c_init(_i2c, 100 * 1000);
    gpio_set_function(_SDA, GPIO_FUNC_I2C);
    gpio_set_function(_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(_SDA);
    gpio_pull_up(_SCL);

    regWrite(0x00, 0b10100000);

    setFreq(50);
}

void PWMController::setFreq(uint16_t freq) {
    int prescale = (25000000 / (freq * 4096)) - 1;
    if (prescale > 255)
        prescale = 255;
    else if (prescale < 3)
        prescale = 3;

    uint8_t mode1 = regRead(0x00);
    regWrite(0x00, (mode1 & ~0b10000000) | 0b00010000);
    regWrite(0xFE, uint8_t(prescale));
    regWrite(0x00, mode1);

    sleep_ms(5);
}

void PWMController::setPWM(uint8_t channel, int16_t pwm) {
    uint8_t data[5];

    data[0] = 0x06 + (4 * channel);
    data[1] = (0);
    data[2] = (0) >> 8;
    data[3] = ((uint16_t)pwm);
    data[4] = ((uint16_t)pwm) >> 8;

    i2c_write_blocking(_i2c, _i2c_address, data, 5, false);
}

long PWMController::map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void PWMController::regWrite(const uint8_t reg, uint8_t value) {
    uint8_t data[2];

    data[0] = reg;
    data[1] = value;

    i2c_write_blocking(_i2c, _i2c_address, data, 2, false);
}
uint8_t PWMController::regRead(const uint8_t reg) {
    uint8_t data[0];

    data[0] = reg;

    i2c_write_blocking(_i2c, _i2c_address, data, 1, false);
    i2c_read_blocking(_i2c, _i2c_address, data, 1, false);

    return data[0];
}
