#include "sensor_files/dht11.h"
#include "sensor_files/bmp.h"
#include "sensor_files/pluviometer.h"
#include "sensor_files/anemometer.h"
#include "sensor_files/windIndicator.h"

// Pin definitions
#define ANE_HALL_PIN 2  // ESP32 pin where the hall sensor is connected - Anemômetro SV10
#define PLU_REED_PIN 13  // ESP32 pin where the magnetic sensor is connected - Pluviômetro
#define DHT_PIN 15 // DHT11
#define WIN_PIN 26 // Indicador de Direção Vento DV10

#define DELAY_TIME 1000  // Time between samples in milliseconds

// Instantiate all sensor classes
DhtSensor dht(DHT_PIN, DHT11);
// BmpSensor bmp;
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

  // // Initialize BMP280
  // bmp.begin(0x76);
  // delay(DELAY_TIME);
  
  // bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
  //                 Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
  //                 Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
  //                 Adafruit_BMP280::FILTER_X16,      /* Filtering. */
  //                 Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  
  // Attach interrupt
  attachInterrupt(digitalPinToInterrupt(ANE_HALL_PIN), countRevolution, RISING);
  attachInterrupt(PLU_REED_PIN, isr_rain, FALLING);
}

void loop() {
  String fullReport = "\n--------------"; 

  fullReport += formatSensorOutput("DHT11", dht);
  delay(DELAY_TIME);  

  // fullReport += formatSensorOutput("BMP280", bmp);
  // delay(DELAY_TIME);  

  fullReport += formatSensorOutput("Pluviômetro", plu);
  delay(DELAY_TIME);  

  fullReport += formatSensorOutput("Anemômetro SV10", ane);
  delay(DELAY_TIME);  

  fullReport += formatSensorOutput("Indicador de Vento DV10", win);
  delay(DELAY_TIME); 

  fullReport += "\n\n--------------\n";

  // Print full report on serial monitor
  Serial.println(fullReport);
}

String formatSensorOutput(const String& name, Sensor& sensor) {
  // return "\n\n" + name + ":"+ "\n" + sensor.getSensorData(); // test sensors locally
  return "\n\n" + name + ":"+ "\n" + sensor.sendSensorData(); // send data to web server
}

