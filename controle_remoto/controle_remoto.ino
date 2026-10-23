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
// Wokwi:       https://wokwi.com/projects/463550930172675073
// ===================================================

// --- Definição dos pinos ---
// IMPORTANTE: No ESP32, os pinos 34 e 35 são os ideais para leitura analógica (ADC)
#define JOYSTICK_X   34   // Eixo X do joystick (ADC)
#define JOYSTICK_Y   35   // Eixo Y do joystick (ADC)
#define BOTAO        17   // Botão de desligar (INPUT_PULLUP)
#define LED_VERDE    25   // Status: conectado / funcionando
#define LED_VERMELHO 26   // Status: desligado / desconectado

// --- Parâmetros do Joystick ---
int centroX = 2048;
int centroY = 2048;
const int ZONA_MORTA = 300; // Ajustado para detectar o movimento no Wokwi

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
  
  // --- CALIBRAÇÃO DO JOYSTICK ---
  Serial.println("Calibrando joystick... NAO MOVA O JOYSTICK!");
  delay(1000); // Tempo para estabilizar
  
  long somaX = 0;
  long somaY = 0;
  for(int i = 0; i < 10; i++) {
    somaX += analogRead(JOYSTICK_X);
    somaY += analogRead(JOYSTICK_Y);
    delay(50);
  }
  centroX = somaX / 10;
  centroY = somaY / 10;

  Serial.print("Centro calibrado -> X: ");
  Serial.print(centroX);
  Serial.print(" | Y: ");
  Serial.println(centroY);
  
  Serial.println("Status: Robo LIGADO e CONECTADO");
  Serial.println("Aguardando comandos...\n");
}

void loop() {
  // --- Leitura do botão de desligar ---
  bool estadoBotao = digitalRead(BOTAO);
  if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    if (roboLigado) {
      roboLigado = false;
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, HIGH);
      Serial.println("Comando enviado: DESLIGAR");
      Serial.println("Robo DESLIGADO remotamente.");
    } else {
      roboLigado = true;
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      Serial.println("Robo RELIGADO. Comunicacao restabelecida.");
    }
    delay(300); // Debounce
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

  String comando = "";

  // Lógica com base no centro calibrado
  if (valorY > centroY + ZONA_MORTA) {
    comando = "FRENTE";
  } else if (valorY < centroY - ZONA_MORTA) {
    comando = "TRAS";
  } else if (valorX > centroX + ZONA_MORTA) {
    comando = "DIREITA";
  } else if (valorX < centroX - ZONA_MORTA) {
    comando = "ESQUERDA";
  }

  // --- Envio do comando ---
  if (comando != "" && (millis() - ultimoEnvio > INTERVALO_ENVIO)) {
    Serial.print("Comando: ");
    Serial.println(comando);
    ultimoEnvio = millis();
  }

  delay(50);
}
