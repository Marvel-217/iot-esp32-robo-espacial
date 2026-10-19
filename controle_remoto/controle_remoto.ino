// ===================================================
// PROJETO: IoT ESP32 - Robô Espacial
// ETAPA: 01 - Controle Remoto no Wokwi
// ===================================================

// --- Definição dos pinos ---
#define JOYSTICK_X   22   // Eixo X do joystick (ADC)
#define JOYSTICK_Y   19   // Eixo Y do joystick (ADC)
#define BOTAO        17   // Botão de desligar (INPUT_PULLUP)
#define LED_VERDE    25   // Status: conectado / funcionando
#define LED_VERMELHO 26   // Status: desligado / desconectado

// --- Parâmetros do Joystick ---
// Centro será calibrado automaticamente no setup()
int centroX = 2048;
int centroY = 2048;
const int ZONA_MORTA = 800; // Zona morta maior para evitar disparos falsos no Wokwi

// --- Variáveis de estado ---
bool roboLigado = true;
bool ultimoEstadoBotao = HIGH;
unsigned long ultimoEnvio = 0;
const unsigned long INTERVALO_ENVIO = 500; // ms

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BOTAO, INPUT_PULLUP);

  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("\n==========================================");
  Serial.println("  CONTROLE REMOTO - ROBO ESPACIAL");
  Serial.println("==========================================");
  
  // --- CALIBRAÇÃO DO JOYSTICK ---
  Serial.println("Calibrando joystick... NAO MOVA O JOYSTICK!");
  delay(1500); // Tempo para o simulador estabilizar
  
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
  // --- Leitura do botão ---
  bool estadoBotao = digitalRead(BOTAO);
  if (estadoBotao == LOW && ultimoEstadoBotao == HIGH) {
    if (roboLigado) {
      roboLigado = false;
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, HIGH);
      Serial.println("Comando enviado: DESLIGAR");
    } else {
      roboLigado = true;
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      Serial.println("Robo RELIGADO. Comunicacao restabelecida.");
    }
    delay(300); 
  }
  ultimoEstadoBotao = estadoBotao;

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
