#include "sensors.h"

// Pin definitions
#define ANE_HALL_PIN 2  // ESP32 pin where the hall sensor is connected - Anemômetro SV10
#define PLU_REED_PIN 13  // ESP32 pin where the magnetic sensor is connected - Pluviômetro
#define DHT_PIN 15 // DHT11
#define WIN_PIN 26 // Indicador de Vento DV10

#define DELAY_TIME 1000  // Time between samples in milliseconds

// Instantiate all sensor classes
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
  bmp.begin(0x76);
  delay(DELAY_TIME);
  
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
  std::string fullReport; 

  // DHT11
  fullReport += formatOutput(dht.getDht());
  delay(DELAY_TIME);  

  // BMP280
  fullReport += formatOutput(bmp.getBmp());
  delay(DELAY_TIME);  

  // Pluviômetro
  fullReport += formatOutput(plu.getRain());
  delay(DELAY_TIME);  

  // Anemômetro SV10
  fullReport += formatOutput(ane.getAnemometer());
  delay(DELAY_TIME);  

  // Indicador de Vento DV10
  fullReport += formatOutput(win.getWindDirection());
  delay(DELAY_TIME);  

  // Print full report on serial monitor
  Serial.println(fullReport.c_str());
}

