#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// Define the I2C address and initialize the BMP280 object
Adafruit_BMP280 bmp; // I2C

// Define the DHT sensor and its pin
#define DHTPIN 26
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  while (!Serial) delay(100);   // Wait for native USB

  // Initialize the BMP280 sensor
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
    while (1) delay(10);  // Loop forever if sensor initialization fails
  }

  // Initialize the DHT11 sensor
  dht.begin();
  
  // Default settings for BMP280 from datasheet
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  // Read temperature and pressure from BMP280
  float bmp_temp = bmp.readTemperature();
  float pressure = bmp.readPressure();

  // Read temperature and humidity from DHT11
  float dht_temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print BMP280 readings to the serial monitor
  Serial.print("BMP280 - TEMP C: ");
  Serial.print(bmp_temp);
  Serial.print(" -- Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  // Print DHT11 readings to the serial monitor
  Serial.print("DHT11 - TEMP C: ");
  Serial.print(dht_temp);
  Serial.print(" -- Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Optional: Read and print altitude from BMP280
  Serial.print("Approx altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  // Delay between readings
  delay(2000);
}



/***************************************************************************
Anemometro Arduino SV10
 ***************************************************************************/

// Pin definitions
# define Hall sensor 2 //  Pino digital 2

// Constants definitions
const float pi = 3.14159265; // Numero pi
int period = 5000; // Tempo de medida(miliseconds)
int delaytime = 2000; // Time between samples (miliseconds)
int radius = 147; // Raio do anemometro(mm)

// Variable definitions
unsigned int Sample = 0; // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned int RPM = 0; // Revolutions per minute
float speedwind = 0; // Wind speed (m/s)
float windspeed = 0; // Wind speed (km/h)

void setup()
{
  // Set the pins
  pinMode(2, INPUT);
  digitalWrite(2, HIGH); //internall pull-up active
    
  //Start serial 
  Serial.begin(9600); // sets the serial port to 9600 baud
  }

void loop()
{
  Sample++;
  Serial.print(Sample);
  Serial.print(": Start measurement...");
  windvelocity();
  Serial.println("   finished.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print(";  RPM: ");
  RPMcalc();
  Serial.print(RPM);
  Serial.print(";  Wind speed: ");
  
//print m/s  
  WindSpeed();
  Serial.print(windspeed);
  Serial.print(" [m/s] ");              
  
//print km/h  
  SpeedWind();
  Serial.print(speedwind);
  Serial.print(" [km/h] ");  
  Serial.println();


  delay(delaytime); //delay between prints
}

// Measure wind speed
void windvelocity(){
  speedwind = 0;
  windspeed = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {
  }
}

void RPMcalc(){
  RPM=((counter)*60)/(period/1000); // Calculate revolutions per minute (RPM)
}

void WindSpeed(){
  windspeed = ((4 * pi * radius * RPM)/60) / 1000; // Calculate wind speed on m/s
 
}

void SpeedWind(){
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6; // Calculate wind speed on km/h
 
}

void addcount(){
  counter++;
} 



#define REED          2    // pin onde o sensor magnetico esta conectado

#define DIAMETRO 125       // diametro interno do balde
#define RAIO     6.25      // raio interno do balde
#define VOLUME   3.05      // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

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
