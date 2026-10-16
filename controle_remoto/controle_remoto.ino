// ===================================================
// PROJETO: IoT ESP32 - Robô Espacial
// ETAPA: 01 - Controle Remoto no Wokwi
// ARQUIVO: controle_remoto.ino
// ---------------------------------------------------
// Descrição:
//   Firmware do controle remoto simulado no Wokwi.
//   Lê o joystick analógico, envia comandos de
//   movimento e permite desligar o robô remotamente.
//
// Repositório: https://github.com/Marvel-217/iot-esp32-robo-espacial
// Wokwi:       https://wokwi.com/projects/SEU_ID_AQUI
// ===================================================

// --- Definição dos pinos ---
#define JOYSTICK_X   22   // Eixo X do joystick (ADC)
#define JOYSTICK_Y   19   // Eixo Y do joystick (ADC)
#define BOTAO        17   // Botão de desligar (INPUT_PULLUP)
#define LED_VERDE    25   // Status: conectado / funcionando
#define LED_VERMELHO 26   // Status: desligado / desconectado

// --- Parâmetros de leitura do joystick ---
#define CENTRO       2048   // Valor central do ADC (12 bits)
#define ZONA_MORTA   500    // Zona morta para evitar ruído

// --- Variáveis de estado ---
bool roboLigado = true;
bool ultimoEstadoBotao = HIGH;
unsigned long ultimoEnvio = 0;
const unsigned long INTERVALO_ENVIO = 500; // ms

void setup() {
  Serial.begin(115200);
  delay(500);

  // Configuração dos pinos
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);

  // Estado inicial: robô ligado, LED verde aceso
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("\n==========================================");
  Serial.println("  CONTROLE REMOTO - ROBO ESPACIAL");
  Serial.println("  Etapa 01 - Wokwi");
  Serial.println("==========================================");
  Serial.println("Status: Robo LIGADO e CONECTADO");
  Serial.println("LED Verde: ACESO | LED Vermelho: APAGADO");
  Serial.println("Aguardando comandos...\n");
}

void loop() {
  // --- Leitura do botão de desligar ---
  bool estadoBotao = digitalRead(BOTAO);
  if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    // Botão pressionado (borda de descida)
    if (roboLigado) {
      roboLigado = false;
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, HIGH);
      Serial.println("Comando enviado: DESLIGAR");
      Serial.println("Robo DESLIGADO remotamente.");
      Serial.println("LED Verde: APAGADO | LED Vermelho: ACESO\n");
    } else {
      // Se já estiver desligado, religa (reconexão)
      roboLigado = true;
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      Serial.println("Robo RELIGADO. Comunicacao restabelecida.");
      Serial.println("LED Verde: ACESO | LED Vermelho: APAGADO\n");
    }
    delay(300); // Debounce simples
  }
  ultimoEstadoBotao = estadoBotao;

  // --- Se o robô estiver desligado, não envia comandos de movimento ---
  if (!roboLigado) {
    delay(100);
    return;
  }

  // --- Leitura do joystick ---
  int valorX = analogRead(JOYSTICK_X);
  int valorY = analogRead(JOYSTICK_Y);

  // --- Determinação da direção ---
  String comando = "";

  if (valorY > CENTRO + ZONA_MORTA) {
    comando = "FRENTE";
  } else if (valorY < CENTRO - ZONA_MORTA) {
    comando = "TRAS";
  } else if (valorX > CENTRO + ZONA_MORTA) {
    comando = "DIREITA";
  } else if (valorX < CENTRO - ZONA_MORTA) {
    comando = "ESQUERDA";
  }

  // --- Envio do comando no Monitor Serial ---
  if (comando != "" && millis() - ultimoEnvio > INTERVALO_ENVIO) {
    Serial.print("Comando: ");
    Serial.println(comando);
    ultimoEnvio = millis();
  }

  // --- Exibição contínua dos valores do joystick (debug) ---
  // Descomente as linhas abaixo se quiser ver os valores brutos
  // Serial.print("X: "); Serial.print(valorX);
  // Serial.print(" | Y: "); Serial.println(valorY);

  delay(50);
}
