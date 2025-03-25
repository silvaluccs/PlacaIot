#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <hardware/structs/io_bank0.h>
#include <leds.h>
#include <pico/stdlib.h>

void inicializar_led_pwm(uint pin_led) {

  gpio_set_function(pin_led, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(pin_led);
  pwm_set_clkdiv(slice_num, 16.f);  // Define o divisor de clock do PWM
  pwm_set_wrap(slice_num, 100);     // Define o valor de wrap (0 passos)
  pwm_set_gpio_level(pin_led, 0);   // Define o Duty Cycle inicial (2,5%)
  pwm_set_enabled(slice_num, true); // Habilita o canal PWM
}

void led_on(uint pin_led, uint wrap) { pwm_set_gpio_level(pin_led, wrap); }
void led_off(uint pin_led) { pwm_set_gpio_level(pin_led, 0); }
