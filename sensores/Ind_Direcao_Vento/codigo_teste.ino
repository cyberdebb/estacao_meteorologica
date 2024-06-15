#define PIN 26

float valor = 0;   // declara a variável inicial em 0
int Winddir = 0;   // Declara o valor inicial em 0

void setup() {
  Serial.begin(9600);         // Define o baud rate em 9600
}

void loop() {
  valor = analogRead(PIN) * (5.0 / 4095.0); // Calcula a tensão para ESP32, onde a resolução ADC é 12-bit (0-4095) e a referência é 3.3V

  // Apresenta os valores da tensão de saída no Monitor Serial
  Serial.print("Leitura do sensor: ");
  Serial.print(valor, 2);  // imprime com duas casas decimais
  Serial.println(" volt");

  // Determina a direção do vento baseada na tensão
  if (valor <= 2.90) {
    Winddir = 0;
    Serial.println("Direção do Vento: Norte");
  } else if (valor <= 3.05) {
    Winddir = 315;
    Serial.println("Direção do Vento: Noroeste");
  } else if (valor <= 3.25) {
    Winddir = 270;
    Serial.println("Direção do Vento: Oeste");
  } else if (valor <= 3.45) {
    Winddir = 225;
    Serial.println("Direção do Vento: Sudoeste");
  } else if (valor <= 3.75) {
    Winddir = 180;
    Serial.println("Direção do Vento: Sul");
  } else if (valor <= 4.00) {
    Winddir = 135;
    Serial.println("Direção do Vento: Sudeste");
  } else if (valor <= 4.25) {
    Winddir = 90;
    Serial.println("Direção do Vento: Leste");
  } else if (valor <= 4.65) {
    Winddir = 45;
    Serial.println("Direção do Vento: Nordeste");
  } else {
    Winddir = 000;
    Serial.println("Direção do Vento: Indeterminada");
  }

  // Imprime o ângulo de direção do vento
  Serial.print("Ângulo: ");
  Serial.print(Winddir);
  Serial.println(" Graus");

  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}