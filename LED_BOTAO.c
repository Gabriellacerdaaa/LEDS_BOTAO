#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos pinos
#define LED_BLUE   11  // LED azul
#define LED_RED    12  // LED vermelho
#define LED_GREEN  13  // LED verde
#define BUTTON     5   // Botão (pushbutton)

// Variável para evitar múltiplas ativações enquanto os LEDs estão acesos
volatile bool leds_active = false;

// Função para desligar o LED verde e permitir nova ativação pelo botão
int64_t turn_off_all_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    leds_active = false;  // Libera o botão para nova ativação
    return 0;
}

// Função para desligar o LED vermelho e acionar o verde após 3s
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    add_alarm_in_ms(3000, turn_off_all_callback, NULL, false);
    return 0;
}

// Função para desligar o LED azul e acionar o vermelho após 3s
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    add_alarm_in_ms(3000, turn_off_red_callback, NULL, false);
    return 0;
}

// Função para detectar o clique do botão
void button_callback(uint gpio, uint32_t events) {
    if (!leds_active) {  // Só ativa se os LEDs estiverem apagados
        leds_active = true;
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
        gpio_put(LED_GREEN, 1);
        add_alarm_in_ms(3000, turn_off_blue_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configuração dos pinos dos LEDs como saída
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    // Configuração do botão como entrada com pull-down interno
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    // Interrupção para detectar clique no botão
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_RISE, true, &button_callback);

    while (1) {
        tight_loop_contents();  // Mantém o loop rodando
    }

    return 0;
}
