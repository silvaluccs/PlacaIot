#include <leds.h>
#include <lwip/tcp.h>
#include <pico/cyw43_arch.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <pico/types.h>
#include <wifi.h>

#include <stack.h>

#include <stdio.h>
#include <string.h>

#define WIFI_SSID "JUNIOR"   // Substitua pelo nome da sua rede Wi-Fi
#define WIFI_PASS "030424Eg" // Substitua pela senha da sua rede Wi-Fi

#define HTTP_RESPONSE_FORMAT                                                   \
  "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nConnection: "          \
  "close\r\n\r\n"                                                              \
  "{ \"status\": \"OK\", \"color\": \"Azul\" }\r\n"

extern Stack stack_request;

// Variável para armazenar a cor atual
char current_color[16] = "Desligado";

// Função de callback para processar requisições HTTP
static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p,
                           err_t err) {
  if (p == NULL) {
    // Cliente fechou a conexão
    tcp_close(tpcb);
    return ERR_OK;
  }

  // Processa a requisição HTTP
  char *request = (char *)p->payload;

  // Resposta de controle de LED em JSON
  char *response = NULL;

  if (strstr(request, "GET /led/blue")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/blue");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/red")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/red");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/green")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/green");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/yellow")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/yellow");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/white")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/white");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/violet")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/violet");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/cyan")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/cyan");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/off")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/off");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/0")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/0");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/100")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/100");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/20")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/20");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/30")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/30");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/40")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/40");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/50")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/50");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/60")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/60");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/70")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/70");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/80")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/80");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/90")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/90");
    push(&stack_request, request);

  } else if (strstr(request, "GET /led/intensity/10")) {
    char *request = malloc(sizeof(char) * 100);
    strcpy(request, "GET /led/intensity/10");
    push(&stack_request, request);
  }

  // Libera o buffer recebido
  pbuf_free(p);

  return ERR_OK;
}
// Callback de conexão: associa o http_callback à conexão
static err_t connection_callback(void *arg, struct tcp_pcb *newpcb, err_t err) {
  tcp_recv(newpcb, http_callback); // Associa o callback HTTP
  return ERR_OK;
}

// Função de setup do servidor TCP
static void start_http_server(void) {
  struct tcp_pcb *pcb = tcp_new();
  if (!pcb) {
    printf("Erro ao criar PCB\n");
    return;
  }

  // Liga o servidor na porta 80
  if (tcp_bind(pcb, IP_ADDR_ANY, 80) != ERR_OK) {
    printf("Erro ao ligar o servidor na porta 80\n");
    return;
  }

  pcb = tcp_listen(pcb);                // Coloca o PCB em modo de escuta
  tcp_accept(pcb, connection_callback); // Associa o callback de conexão

  printf("Servidor HTTP rodando na porta 80...\n");
}

void init_wifi() {
  printf("Iniciando servidor HTTP\n");

  // Inicializa o Wi-Fi
  if (cyw43_arch_init()) {
    printf("Erro ao inicializar o Wi-Fi\n");
    return;
  }

  cyw43_arch_enable_sta_mode();
  printf("Conectando ao Wi-Fi...\n");

  if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS,
                                         CYW43_AUTH_WPA2_AES_PSK, 10000)) {
    printf("Falha ao conectar ao Wi-Fi\n");
    return;
  } else {
    printf("Connected.\n");
    // Read the ip address in a human readable way
    uint8_t *ip_address = (uint8_t *)&(cyw43_state.netif[0].ip_addr.addr);
    printf("Endereço IP %d.%d.%d.%d\n", ip_address[0], ip_address[1],
           ip_address[2], ip_address[3]);
  }

  printf("Wi-Fi conectado!\n");

  // Inicia o servidor HTTP
  start_http_server();
}
