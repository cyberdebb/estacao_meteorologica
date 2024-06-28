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
  if ((valor >= 0 && valor <= 0.60)) {
    Winddir = 0;
    windDirection = "Norte";
  } else if (valor > 0.60 && valor <= 0.80) {
    Winddir = 315;
    windDirection = "Noroeste";
  } else if (valor > 0.80 && valor <= 0.93) {
    Winddir = 270;
    windDirection = "Oeste";
  } else if (valor > 0.93 && valor <= 1.08) {
    Winddir = 225;
    windDirection = "Sudoeste";
  } else if (valor > 1.08 && valor <= 1.15) {
    Winddir = 180;
    windDirection = "Sul";
  } else if (valor > 1.15 && valor <= 1.40) {
    Winddir = 135;
    windDirection = "Sudeste";
  } else if (valor > 1.40 && valor <= 1.85) {
    Winddir = 90;
    windDirection = "Leste";
  } else if (valor > 1.85 && valor <= 2.50) {
    Winddir = 45;
    windDirection = "Nordeste";
  } else {
    Winddir = 000;  // Default to 0 if direction is indeterminate
    windDirection = "Indeterminada";
  }

  // Imprime o ângulo de direção do vento
  Serial.print("Ângulo: ");
  Serial.print(Winddir);
  Serial.println(" Graus");

  delay(5000);  // Aguarda 5 segundos antes da próxima leitura
}