#ifndef LEDS_H
#define LEDS_H

#include <pico/stdlib.h>

typedef enum colors {
    Red,
    Blue,
    Green,
    White,
    Cyan,
    Violet,
    Yellow,
    Black

} colors;

void init_led_pwm(uint pin_led);
void led_on(uint pin_led, uint wrap);
void led_off(uint pin_led);
void select_color(colors color, uint wrap, uint pin_led_blue, uint pin_led_red,
    uint pin_led_green);

#endif
