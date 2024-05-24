#include "sensors.h"

// Pin definitions
#define ANE_HALL_PIN 2  // ESP32 pin where the hall sensor is connected - Anemômetro SV10
#define PLU_REED_PIN 3  // ESP32 pin where the magnetic sensor is connected - Pluviômetro
#define DHT_PIN 15 // DHT11
#define WIN_PIN 36 // Indicador de Vento DV10

#define DELAY_TIME 1000  // Time between samples in milliseconds

DhtSensor dht(DHT_PIN, DHT11);
BmpSensor bmp;
PluviometerSensor plu;
AnemometerSensor ane;
WindIndicatorSensor win(WIN_PIN);

void setup() {
  // Initialize the pins
  pinMode(ANE_HALL_PIN, INPUT_PULLUP); // Set pin as input with internal pull-up
  pinMode(PLU_REED_PIN, INPUT_PULLUP); // Set pin as input with internal pull-up

  // Start serial communication
  Serial.begin(9600);

  // Initialize DHT11
  dht.begin();
  delay(DELAY_TIME);

  // Initialize BMP280
  if (!bmp.begin(0x76)) {
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
  
  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(ANE_HALL_PIN), countRevolution, RISING);
  attachInterrupt(PLU_REED_PIN, isr_rain, FALLING);
}

void loop() {
  // DHT11
  dht.getDht();

  //BMP280
  bmp.getBmp();

  // Pluviômetro
  plu.getRain();

  // Anemômetro SV10
  ane.getAnemometer();

  // Indicador de Vento DV10
  win.getWindDirection();

  // Delay between prints
  delay(DELAY_TIME);  
}

