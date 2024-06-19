#ifndef DHT11_H
#define DHT11_H

#include "../sensor.h"
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// DHT11 sensor class
class DhtSensor : public Sensor {
  private:
    DHT dht;
    float temperature = 0;
    float humidity = 0;

  public: 
    DhtSensor(uint8_t pin, uint8_t type);
    void begin();
    void getData();
    String getSensorData() override;
    String sendSensorData() override;
    ~DhtSensor();
};

DhtSensor::DhtSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

void DhtSensor::begin() {
  dht.begin();
}

void DhtSensor::getData() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

// Test sensors locally
String DhtSensor::getSensorData() {
  getData();
  
  char buffer[100];
  snprintf(buffer, sizeof(buffer), "TEMP C %.2f -- Umidade %.2f%%", temperature, humidity);  
  
  return String(buffer);
}

// Send data to web server
String DhtSensor::sendData() {
  getData();

  char buffer[100];
  int idStation = 1;

  snprintf(buffer, sizeof(buffer), "{\"idStation\": \"1\", \"temperature\": \"%.2f\", \"humidity\": \"%.2f\"}", temperature, humidity);

  sendData("dht", buffer);
  return String(buffer);
}

DhtSensor::~DhtSensor() {}

#endif