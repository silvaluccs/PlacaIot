#include "leds.h"
#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <lwip/tcp.h>
#include <pico.h>
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <stdbool.h>
#include <wifi.h>

const uint led_vermelho = 13;
const uint led_azul = 12;
const uint led_verde = 11;

bool repeating_timer_callback(struct repeating_timer *t);

int main() {
  stdio_init_all(); // Inicializa a saída padrão
  sleep_ms(10000);

  init_wifi();
  init_led_pwm(led_vermelho);
  init_led_pwm(led_azul);
  init_led_pwm(led_verde);

  struct repeating_timer timer;
  add_repeating_timer_ms(100, repeating_timer_callback, NULL, &timer);

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
