/***************************************************************************
BMP280
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_BMP280.h>

// Define the I2C address and initialize the BMP280 object
Adafruit_BMP280 bmp; // I2C

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  while (!Serial) delay(100);   // Wait for native USB

  // Initialize the BMP280 sensor
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
    while (1) delay(10);  // Loop forever if sensor initialization fails
  }

  // Default settings from datasheet
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  // Read temperature and pressure
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure();

  // Print temperature and pressure to the serial monitor
  Serial.print("TEMP C ");
  Serial.print(temp);
  Serial.print(" -- Pressure ");
  Serial.print(pressure);
  Serial.println(" Pa");

  // Optional: Read and print altitude
  Serial.print("Approx altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  // Delay between readings
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
// usar 5V

// Pin definitions
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
// usar 3.3V

int pin = A0;  // Declara o pino analógico 0 como "pin"
float valor = 0;   // declara a variável inicial em 0
int Winddir = 0;   // Declara o valor inicial em 0

void setup() {
  Serial.begin(9600);         // Define o baud rate em 9600
  analogReference(DEFAULT);
}

void loop() {
  valor = analogRead(pin) * (3.3 / 4095.0); // Calcula a tensão para ESP32, onde a resolução ADC é 12-bit (0-4095) e a referência é 3.3V

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);       // velocidade monitor serial

  pinMode(REED, INPUT_PULLUP);
  attachInterrupt(REED, isr_rain, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  get_rain();

}
