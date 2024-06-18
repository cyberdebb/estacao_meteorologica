#ifndef BMP_H
#define BMP_H

#include "../sensor.h"
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <WiFi.h>


const char* ssid = "Cowork-Extensao"; // "SUA_REDE_WIFI"
const char* password = "extensaocts"; // "SUA_SENHA"


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
  int idStation = 1;

  // snprintf(buffer, sizeof(buffer),
  //            '{\"pressure\": \"%.2f\",\"temperature\": \"%.2f\",  \"altitude\":\"%.2f\" }'idStation,  pressure,temperature,altitude);

  snprintf(buffer, sizeof(buffer),
             '{\"idStation\": \"%d\", \"pressure\": \"%.2f\",\"temperature\": \"%.2f\",  \"altitude\":\"%.2f\" }'idStation,  pressure,temperature,altitude);

  
  // ---------------------------------------------------------------------------
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://estacao-meteorologica.vercel.app/bmp");  
    http.addHeader("Content-Type", "application/json");

   
    Serial.println(buffer);
    
    
    int httpResponseCode = http.POST(buffer);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Erro no envio, código: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  else {
    Serial.println("Não há conexão Wi-Fi disponível. Tentando reconectar...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
}

  // ---------------------------------------------------------------------------
 // acho que nao precisa do return 
  return String(buffer);
}

BmpSensor::~BmpSensor() {}

#endif