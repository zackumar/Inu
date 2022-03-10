#include "pwm_driver.h"

#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

void PWMDriver::PWMDriver() {
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
}

void begin();

void reset() {


}

void sleep();
void wakeup();

void setPWMFreq(float freq);
void setPWM(uint8_t num, uint16_t on, uint16_t off);
void setOscillatorFrequency(uint32_t freq);

void PWMDriver::write8(uint8_t addr, uint8_t data) {
    i2c_write_blocking
}