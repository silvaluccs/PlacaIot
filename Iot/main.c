#include "leds.h"
#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <lwip/tcp.h>
#include <pico.h>
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stack.h>
#include <stdbool.h>
#include <wifi.h>

Stack stack_request;
colors current_color_led = Black;
uint wrap = 100;

const uint pin_led_red = 13;
const uint pin_led_blue = 12;
const uint pin_led_green = 11;

bool repeating_timer_request_callback(struct repeating_timer *t);
bool repeating_timer_callback(struct repeating_timer *t);

int main() {
  stdio_init_all(); // Inicializa a saída padrão
  sleep_ms(10000);

  init_stack(&stack_request);
  init_wifi();
  init_led_pwm(pin_led_red);
  init_led_pwm(pin_led_blue);
  init_led_pwm(pin_led_green);

  struct repeating_timer timer;
  add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);

  struct repeating_timer timer_request;
  add_repeating_timer_ms(10, repeating_timer_request_callback, NULL,
                         &timer_request);

  while (true) {
    tight_loop_contents();
  }

  cyw43_arch_deinit(); // Desliga o Wi-Fi (não será chamado, pois o loop é
                       // infinito)
  return 0;
}

bool repeating_timer_callback(struct repeating_timer *t) {

  cyw43_arch_poll();

  return true;
}

bool repeating_timer_request_callback(struct repeating_timer *t) {

  if (isEmpty(&stack_request)) {
    return true;
  }

  char *request = top(&stack_request);
  process_request(request);
  pop(&stack_request);

  return true;
}
