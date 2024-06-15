#ifndef DHT11_H
#define DHT11_H

#include "../sensor.h"
#include <DHT.h>
#include <time.h>

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

// void read_dht_temp(char* temp_str) {
//     float temp = dht.readTemperature();
//     dtostrf(temp, 4, 2, temp_str);
// }

// void read_dht_humidity(char* humidity_str) {
//     float humidity = dht.readHumidity();
//     dtostrf(humidity, 4, 2, humidity_str);
// }

// void get_current_datetime(char* buffer, size_t buffer_size) {
//     time_t now = time(NULL);
//     struct tm* tm_info = localtime(&now);
//     strftime(buffer, buffer_size, "%H:%M:%S %d/%m/%Y", tm_info);
// }

String DhtSensor::getSensorData() {
  //getData();

  //char buffer[80];
  //snprintf(buffer, sizeof(buffer), "TEMP C %.2f -- Umidade %.2f%%", temperature, humidity);

  char temp_str[6];  // "xx.xx" + null terminator
  char humidity_str[6];  // "xx.xx" + null terminator
  char datetime[20];
  get_current_datetime(datetime, sizeof(datetime));

    // Formatação dos valores
  // read_dht_temp(temp_str);
  // read_dht_humidity(humidity_str);

  // Formatação do JSON
  char json_buffer[100];

  snprintf(json_buffer, sizeof(json_buffer), "{\"idStation\": \"%d\", \"temperatura\": \"%s\", \"umidade\": \"%s\"}",  idStation, temp_str, humidity_str);

  return String(json_buffer);
}

DhtSensor::~DhtSensor() {}

#endif