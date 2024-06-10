#ifndef BMP_H
#define BMP_H

#include "../sensor.h"
#include <Adafruit_BMP280.h>
#include <Wire.h>

// BMP280 sensor class
class BmpSensor : public Sensor {
  private:
    Adafruit_BMP280 bmp;
    float temperature = 0;
    float pressure = 0;
    float altitude = 0;

  public:
    BmpSensor();
    bool begin(uint8_t address);
    uint8_t sensorID();
    void setSampling(Adafruit_BMP280::sensor_mode mode, Adafruit_BMP280::sensor_sampling tempSampling, Adafruit_BMP280::sensor_sampling pressSampling, Adafruit_BMP280::sensor_filter filter, Adafruit_BMP280::standby_duration duration);
    void getData();
    String getSensorData() override;
    ~BmpSensor();
};

BmpSensor::BmpSensor() {}

bool BmpSensor::begin(uint8_t address) {
  return bmp.begin(address); 
}

uint8_t BmpSensor::sensorID() {
  return bmp.sensorID();
}

void BmpSensor::setSampling(Adafruit_BMP280::sensor_mode mode, Adafruit_BMP280::sensor_sampling tempSampling, Adafruit_BMP280::sensor_sampling pressSampling, Adafruit_BMP280::sensor_filter filter, Adafruit_BMP280::standby_duration duration) {
  bmp.setSampling(mode, tempSampling, pressSampling, filter, duration);
}

void BmpSensor::getData() {
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure();
  altitude = bmp.readAltitude(1011);
}

String BmpSensor::getSensorData() {
  getData();

  char buffer[150];
  //snprintf(buffer, sizeof(buffer), "Temperature = %.2f *C\nPressure = %.2f Pa\nApprox altitude = %.2f m", temperature, pressure, altitude);
  int idStation = 1;

  snprintf(buffer, sizeof(buffer),
             "{\"BMP280\": [{\"pressure\": %.2f, \"temperature\": %.2f, \"altitude\": %.2f, \"idStation\": %d}]}",
             pressure, temperature, altitude, idStation);
  return String(buffer);
}

/*
{
    "BMP280": [
        {
            "pressure": 0.00,
            "temperature": 0.00,
            "altitude": 0.00,
            "idStation": 0
        }
    ]
}
*/

BmpSensor::~BmpSensor() {}

#endif