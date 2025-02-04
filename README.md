# 💡 Projeto: Sequência de LEDs com Interrupção por Botão

Este projeto demonstra o uso de *GPIOs* e *alarms* na plataforma **Raspberry Pi Pico** (ou Bitdoglab) para controlar uma sequência de LEDs com base na interação de um botão. Ao pressionar o botão, os LEDs (azul, vermelho e verde) acendem simultaneamente e, após intervalos de 3 segundos, são desligados em sequência.

---

## 🎯 Objetivos

- **Controlar LEDs**: Acender e apagar os LEDs conectados aos pinos 11 (azul), 12 (vermelho) e 13 (verde).
- **Interrupção via Botão**: Utilizar um botão (pino 5) para iniciar a sequência de desligamento dos LEDs.
- **Gerenciamento de Tempo**: Utilizar funções de *alarm* para gerenciar os intervalos de 3 segundos entre as transições.

---

## 📚 Descrição do Funcionamento

1. **Configuração Inicial**:
   - Os pinos dos LEDs são configurados como saída.
   - O pino do botão é configurado como entrada com *pull-up* para detectar os eventos de borda de subida.

2. **Acionamento do Botão**:
   - Ao pressionar o botão, se os LEDs estiverem apagados (variável `leds_active` for `false`), todos os LEDs acendem.
   - A variável `leds_active` é setada como `true` para evitar que a sequência seja reiniciada enquanto ela ainda está em andamento.

3. **Sequência de Desligamento**:
   - **Primeira Fase**: Após 3 segundos, a função `turn_off_blue_callback` é chamada, desligando o LED azul e agendando a próxima etapa.
   - **Segunda Fase**: Outros 3 segundos depois, `turn_off_red_callback` desliga o LED vermelho e agenda o desligamento do LED verde.
   - **Terceira Fase**: Após mais 3 segundos, `turn_off_all_callback` desliga o LED verde e reinicia o sistema para permitir nova ativação.

4. **Loop Principal**:
   - O loop principal utiliza `tight_loop_contents()` para manter o programa ativo sem interferir na lógica de interrupção.

---

## 🛠️ Como Compilar e Executar

1. **Configuração do Ambiente**:
   - Certifique-se de que o SDK do Raspberry Pi Pico (ou Bitdoglab) esteja devidamente instalado e configurado.
   - Configure o *toolchain* para compilar o código em C.

2. **Compilação**:
   - Utilize *CMake* e *Make* para compilar o projeto:
     ```sh
     mkdir build
     cd build
     cmake ..
     make
     ```
3. **Upload para a Placa**:
   - Após a compilação, será gerado um arquivo `.uf2`. Conecte sua placa via USB (em modo bootloader) e copie o arquivo para a unidade correspondente.

4. **Execução**:
   - Pressione o botão para iniciar a sequência dos LEDs e observe as mudanças conforme os intervalos definidos.

---

## 📝 Considerações Finais

- **Controle de Concurrency**: A variável `leds_active` garante que o sistema não reinicie a sequência enquanto o ciclo atual não tiver finalizado.
- **Uso de Alarmes**: As funções `add_alarm_in_ms` demonstram uma gestão precisa dos intervalos de tempo, essencial para aplicações em sistemas embarcados.
- **Interrupções**: A configuração de interrupção para o botão possibilita uma resposta imediata sem interromper o funcionamento contínuo do programa.

---

## 🔗 Referências

- [Documentação do Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [Exemplos e Tutoriais do SDK Pico](https://github.com/raspberrypi/pico-examples)

---

**Desenvolvido por [GABRIEL SANTOS DE LACERDA]**  
*ESTUDANTE ENGENHARIA ELÉTRICA - UFOB*  
Bitdoglab 🚀

