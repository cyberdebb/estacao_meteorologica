#ifndef DHT11_H
#define DHT11_H

#include "../sensor.h"
#include <DHT.h>

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
    String getJsonData() override;
    String getSensorData() override;
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

String DhtSensor::getJsonData() {
  getData();

  DynamicJsonDocument doc(256);
  doc["temperatura"] = temperature;
  doc["umidade"] = humidity;

  String jsonData;
  serializeJson(doc, jsonData);

  return jsonData;
}

String DhtSensor::getSensorData() {
  getData();

  char buffer[80];
  snprintf(buffer, sizeof(buffer), "TEMP C %.2f -- Umidade %.2f%%", temperature, humidity);
  return String(buffer);
}

DhtSensor::~DhtSensor() {}

#endif