#include <stdio.h>

#include "pico/stdlib.h"

const uint led_pin = 25;

int main() {
    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    // Loop forever
    while (true) {
        // Blink LED
        printf("Blinking Pt. 2!\r\n");
        gpio_put(led_pin, true);
        sleep_ms(500);
        gpio_put(led_pin, false);
        sleep_ms(500);
    }
}

void loop() {
}