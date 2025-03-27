#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <hardware/structs/io_bank0.h>
#include <leds.h>
#include <pico/stdlib.h>
#include <pico/types.h>

void init_led_pwm(uint pin_led) {

  gpio_set_function(pin_led, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(pin_led);
  pwm_set_clkdiv(slice_num, 16.f);  // Define o divisor de clock do PWM
  pwm_set_wrap(slice_num, 100);     // Define o valor de wrap (0 passos)
  pwm_set_gpio_level(pin_led, 0);   // Define o Duty Cycle inicial (2,5%)
  pwm_set_enabled(slice_num, true); // Habilita o canal PWM
}

void led_on(uint pin_led, uint wrap) { pwm_set_gpio_level(pin_led, wrap); }
void led_off(uint pin_led) { pwm_set_gpio_level(pin_led, 0); }

void select_color(colors color, uint wrap, uint pin_led_blue, uint pin_led_red,
                  uint pin_led_green) {

  switch (color) {
  case Blue:
    led_on(pin_led_blue, wrap);
    led_off(pin_led_red);
    led_off(pin_led_green);
    break;
  case Red:
    led_on(pin_led_red, wrap);
    led_off(pin_led_blue);
    led_off(pin_led_green);
    break;
  case Green:
    led_on(pin_led_green, wrap);
    led_off(pin_led_blue);
    led_off(pin_led_red);
    break;
  case Yellow:
    led_on(pin_led_blue, wrap);
    led_on(pin_led_green, wrap);
    led_off(pin_led_red);
    break;
  case White:
    led_on(pin_led_blue, wrap);
    led_on(pin_led_green, wrap);
    led_on(pin_led_red, wrap);
    break;
  case Violet:
    led_on(pin_led_red, wrap);
    led_off(pin_led_green);
    led_on(pin_led_blue, wrap);
    break;
  case Cyan:
    led_on(pin_led_blue, wrap);
    led_on(pin_led_green, wrap);
    led_off(pin_led_red);
    break;
  case (Black):
    led_off(pin_led_blue);
    led_off(pin_led_red);
    led_off(pin_led_green);
    break;
  }
}
