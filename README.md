# 🤖 IoT ESP32 – Robô Espacial

Projeto desenvolvido para a **Atividade AV2 – Camada de Serviço** do curso **SENAI CIMATEC**, com foco em **Práticas Integradas: Camada de Percepção**.

---

## 🎯 Objetivo da Etapa 01

Criar o **controle remoto simulado** de um robô explorador espacial utilizando **ESP32** e o simulador **Wokwi**.

O controle remoto é responsável por:
- Ler os comandos do **joystick analógico** (4 direções: frente, trás, esquerda, direita).
- Enviar o comando **"DESLIGAR"** ao robô através de um botão.
- Indicar o estado da comunicação através de **LEDs verde e vermelho**.
- Exibir todos os comandos enviados no **Monitor Serial**.

---

## 🧩 Lista dos Componentes do Circuito

| Componente | Quantidade | Pino ESP32 | Função |
|---|---|---|---|
| ESP32 | 1 | — | Microcontrolador principal |
| Joystick Analógico | 1 | GPIO 22 (X) / GPIO 19 (Y) | Envia comandos de movimento |
| Botão (Push Button) | 1 | GPIO 17 | Envia comando "DESLIGAR" |
| LED Verde | 1 | GPIO 25 | Indica controle conectado |
| LED Vermelho | 1 | GPIO 26 | Indica robô desligado/desconectado |
| Resistor 220Ω | 2 | — | Limitador de corrente dos LEDs |

### 🔌 Diagrama de Conexões

```
ESP32                    Componentes
─────────────────────────────────────────
GPIO 22  ──────────────► VRx (Joystick)
GPIO 19  ──────────────► VRy (Joystick)
3V3      ──────────────► VCC (Joystick)
GND      ──────────────► GND (Joystick)

GPIO 17  ──────────────► Botão (terminal 1)
GND      ──────────────► Botão (terminal 2)

GPIO 25  ──[220Ω]──────► LED Verde (ânodo)
GND      ──────────────► LED Verde (cátodo)

GPIO 26  ──[220Ω]──────► LED Vermelho (ânodo)
GND      ──────────────► LED Vermelho (cátodo)
```

---

## 🔗 Link do Projeto no Wokwi

👉 **[Clique aqui para acessar o projeto no Wokwi](https://wokwi.com/projects/463550930172675073)**

---

## ▶️ Como Rodar no Wokwi

1. Acesse [https://wokwi.com](https://wokwi.com) e faça login (ou crie uma conta gratuita).
2. Crie um **novo projeto ESP32**.
3. Adicione os componentes listados acima.
4. Faça as conexões conforme o **diagrama de conexões**.
5. Copie o código do arquivo [`controle_remoto.ino`](./controle_remoto/controle_remoto.ino) e cole no editor do Wokwi.
6. Clique em **"Start Simulation"** (▶️).
7. Abra o **Monitor Serial** e configure para **115200 baud**.
8. Teste os comandos:

| Ação | Resultado Esperado |
|---|---|
| Mover joystick para cima | `Comando: FRENTE` |
| Mover joystick para baixo | `Comando: TRAS` |
| Mover joystick para direita | `Comando: DIREITA` |
| Mover joystick para esquerda | `Comando: ESQUERDA` |
| Pressionar botão | `Comando enviado: DESLIGAR` |

---

## 🧠 Lógica do Firmware

O firmware executa as seguintes etapas continuamente:

1. **Leitura do botão** (GPIO 17): ao ser pressionado, envia o comando `"DESLIGAR"` e acende o LED vermelho.
2. **Leitura do joystick** (GPIO 22 e 19): valores acima/abaixo de uma zona morta determinam a direção.
3. **Envio do comando** no Monitor Serial (ex.: `Comando: FRENTE`).
4. **Atualização dos LEDs** conforme o estado da comunicação:
   - 🟢 Verde aceso → robô ligado e conectado.
   - 🔴 Vermelho aceso → robô desligado/desconectado.

---

## 📌 Entregáveis da Etapa 01

- ✅ Projeto funcionando no Wokwi (joystick, botão e LEDs).
- ✅ Link do projeto no README do GitHub.
- ✅ Código do firmware versionado no GitHub.

---

## 🛠️ Tecnologias Utilizadas

- **ESP32** – Microcontrolador
- **Arduino IDE / Wokwi** – Ambiente de desenvolvimento
- **Git / GitHub** – Versionamento de código
- **Linguagem C++** (Arduino framework)

---

## 👥 Autores

- **Marvel-217** – [GitHub](https://github.com/Marvel-217)

---

## 📚 Referências

- ESPRESSIF SYSTEMS. *ESP32 Technical Reference Manual*. Shanghai: Espressif, 2022.
- WOKWI. *Online ESP32 and Arduino Simulator*. Disponível em: https://wokwi.com/
- RANDOM NERD TUTORIALS. *ESP32 Tutorials and Projects*. Disponível em: https://randomnerdtutorials.com/
- ARDUINO. *Arduino IDE*. Disponível em: https://www.arduino.cc/en/software
