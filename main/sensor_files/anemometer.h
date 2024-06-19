#ifndef ANEMOMETER_H
#define ANEMOMETER_H

#define PERIOD 5000 // Measurement period in milliseconds
#define RADIUS 147 // Anemometer radius in mm

#include "../sensor.h"

// Anemometer SV10 Arduino sensor class
class AnemometerSensor : public Sensor {
  private:
    unsigned int rpm = 0;  // Revolutions per minute
    float windSpeedMetersPerSecond = 0;  // Wind speed in m/s
    float windSpeedKilometersPerHour = 0;  // Wind speed in km/h

  public:
    static volatile unsigned int counter; // Magnet counter for sensor
    
    AnemometerSensor();
    void measureWindSpeed();
    void calculateRPM();
    void calculateWindSpeedMetersPerSecond();
    void calculateWindSpeedKilometersPerHour();
    void getData();
    String getSensorData() override;
    String sendData() override;
    ~AnemometerSensor();
};

AnemometerSensor::AnemometerSensor() {}

void AnemometerSensor::measureWindSpeed() {
  counter = 0;  
  long startTime = millis();
  while (millis() < startTime + PERIOD) {}; // Wait for the period to complete
}

void AnemometerSensor::calculateRPM() {
  rpm = (counter * 60) / (PERIOD / 1000); // Calculate RPM
}

void AnemometerSensor::calculateWindSpeedMetersPerSecond() {
  windSpeedMetersPerSecond = ((4 * PI * RADIUS * rpm) / 60) / 1000; // Calculate wind speed in m/s
}

void AnemometerSensor::calculateWindSpeedKilometersPerHour() {
  windSpeedKilometersPerHour = windSpeedMetersPerSecond * 3.6; // Convert m/s to km/h
}

void AnemometerSensor::getData() {
  measureWindSpeed();
  calculateRPM();
  calculateWindSpeedMetersPerSecond();
  calculateWindSpeedKilometersPerHour();
}

// Testing sensors locally
String AnemometerSensor::getSensorData() {
  getData();

  char buffer[200];
  snprintf(buffer, sizeof(buffer), "Counter: %u; RPM: %u; Wind speed: %.2f [m/s] %.2f [km/h]", counter, rpm, windSpeedMetersPerSecond, windSpeedKilometersPerHour);
  
  return String(buffer);
}

// Send data to web server
String AnemometerSensor::sendData() {
  getData();

  char buffer[200];
  snprintf(buffer, sizeof(buffer), "Counter: %u; RPM: %u; Wind speed: %.2f [m/s] %.2f [km/h]", counter, rpm, windSpeedMetersPerSecond, windSpeedKilometersPerHour);
  
  return String(buffer);
}

AnemometerSensor::~AnemometerSensor() {}

// Defining static interruption variables
volatile unsigned int AnemometerSensor::counter = 0;

// Anemometer Interruption function
static void countRevolution() {
  AnemometerSensor::counter++; // Increment counter for each revolution detected
}

#endif
