#ifndef WIFI_H
#define WIFI_H

#include <pico/stdlib.h>
#include <lwip/tcp.h>
#include <pico/cyw43_arch.h>

static err_t http_callback(void* arg, struct tcp_pcb* tpcb, struct pbuf* p, err_t err);
static err_t connection_callback(void* arg, struct tcp_pcb* newpcb, err_t err);
static void start_http_server(void);
void init_wifi();

#endif // !WIFI_H
