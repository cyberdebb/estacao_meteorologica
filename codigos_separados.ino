/***************************************************************************
BMP280
 ***************************************************************************/
#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  Serial.println(F("BMP280 test"));
  unsigned status;
  status = bmp.begin(0x76 , &Wire);

  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
    Serial.print("SensorID was: 0x"); 
    Serial.println(bmp.sensorID(),16);
    Serial.print("ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("ID of 0x60 represents a BME 280.\n");
    Serial.print("ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1011)); 
    Serial.println(" m");

    Serial.println();
    delay(2000);
}

/***************************************************************************
DHT11
 ***************************************************************************/
#include <DHT.h>

DHT dht(15,DHT11);

void setup() {
  // put your setup code here, to run once:
 dht.begin();
 delay(2000);

 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
 float temp = dht.readTemperature();
 float umidade = dht.readHumidity();

 Serial.print("TEMP C ");
 Serial.print(temp);

 Serial.print(" -- Umidade ");
 Serial.print(umidade);
 Serial.println(" % ");
 delay(2000);
}


/***************************************************************************
Anemometro Arduino SV10
 ***************************************************************************/
#define HALL_SENSOR_PIN 2  // ESP32 pin where the hall sensor is connected

// Constants definitions
const int PERIOD = 5000;  // Measurement period in milliseconds
const int DELAY_TIME = 2000;  // Time between samples in milliseconds
const int RADIUS = 147;  // Anemometer radius in mm

// Variable definitions
unsigned int sampleNumber = 0;  // Sample number
volatile unsigned int counter = 0; // Magnet counter for sensor
unsigned int rpm = 0;  // Revolutions per minute
float windSpeedMetersPerSecond = 0;  // Wind speed in m/s
float windSpeedKilometersPerHour = 0;  // Wind speed in km/h

void setup() {
  // Initialize the pin
  pinMode(HALL_SENSOR_PIN, INPUT_PULLUP);  // Set pin as input with internal pull-up

  // Start serial communication
  Serial.begin(9600);
  
  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PIN), countRevolution, RISING);
}

void loop() {
  sampleNumber++;
  Serial.print(sampleNumber);
  Serial.print(": Start measurement...");
  measureWindSpeed();
  Serial.println(" finished.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print("; RPM: ");
  calculateRPM();
  Serial.print(rpm);
  Serial.print("; Wind speed: ");
  
  // Print wind speed in m/s
  calculateWindSpeedMetersPerSecond();
  Serial.print(windSpeedMetersPerSecond);
  Serial.print(" [m/s] ");              
  
  // Print wind speed in km/h
  calculateWindSpeedKilometersPerHour();
  Serial.print(windSpeedKilometersPerHour);
  Serial.print(" [km/h] ");  
  Serial.println();

  delay(DELAY_TIME);  // Delay between prints
}

void measureWindSpeed() {
  counter = 0;  
  long startTime = millis();
  while (millis() < startTime + PERIOD) {
    // Wait for the period to complete
  }
}

void calculateRPM() {
  rpm = (counter * 60) / (PERIOD / 1000);  // Calculate RPM
}

void calculateWindSpeedMetersPerSecond() {
  windSpeedMetersPerSecond = ((4 * PI * RADIUS * rpm) / 60) / 1000;  // Calculate wind speed in m/s
}

void calculateWindSpeedKilometersPerHour() {
  windSpeedKilometersPerHour = windSpeedMetersPerSecond * 3.6;  // Convert m/s to km/h
}

void countRevolution() {
  counter++;  // Increment counter for each revolution detected
}

/***************************************************************************
Indicador de vento DV10 
 ***************************************************************************/
#define PIN 36

float valor = 0;   // declara a variável inicial em 0
int Winddir = 0;   // Declara o valor inicial em 0

void setup() {
  Serial.begin(9600);         // Define o baud rate em 9600
  analogReference(DEFAULT);
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

/***************************************************************************
Pluviômetro
 ***************************************************************************/
#define REED 2    // pin onde o sensor magnetico esta conectado

#define DIAMETRO 125       // diametro interno do balde
#define RAIO 6.25      // raio interno do balde
#define VOLUME 3.05      // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

// Variáveis pluviometro:
int val = 0;
int old_val = 0;
volatile unsigned long REEDCOUNT = 0;
float volume_coletado;

// This is the function that the interrupt calls to increment the turning count
void IRAM_ATTR isr_rain () {
  if ((millis() - ContactBounce) > 50 ) { // debounce the switch contact.
    REEDCOUNT = REEDCOUNT + 1;              // Adiciona 1 à cntagem de pulsos
    ContactBounce = millis();
    // Serial.println("funcao interrupcao chuva");
  }
}

void get_rain(){
    // float area_recipiente = 3.14159265 * (RAIO * RAIO); // área da seção transversal do recipiente em cm²
    // float volume_por_virada = (VOLUME/area_recipiente);
    volume_coletado = (REEDCOUNT * 0.25) * 10; // volume total coletado em cm³

    Serial.print("Viradas: ");
    Serial.println(REEDCOUNT);

    Serial.print("Chuva: ");
    Serial.print (volume_coletado);
    Serial.println(" mm");
}

void setup() {
  Serial.begin(115200);       // velocidade monitor serial

  pinMode(REED, INPUT_PULLUP);
  attachInterrupt(REED, isr_rain, FALLING);
}

void loop() {
  get_rain();
  delay(1000);
}
