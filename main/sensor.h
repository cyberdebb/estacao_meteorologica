#ifndef SENSOR_H
#define SENSOR_H

#include "includes.h"

class Sensor {
  public:
    virtual ~Sensor() {};
    virtual String getSensorData() = 0;
    virtual String sendSensorData() = 0;
    void sendData(String sensorName, String buffer);
};

void Sensor::sendData(String sensorName, String buffer) {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL + sensorName);  
    http.addHeader("Content-Type", "application/json");

    Serial.println(sensorName);
    Serial.println(buffer);
    
    int httpResponseCode = http.POST(buffer);

    if (httpResponseCode > 0) {
      Serial.println(httpResponseCode);
      Serial.println(http.getString());
    } else {
      Serial.print("Erro no envio, código: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Não há conexão Wi-Fi disponível. Tentando reconectar...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
  }
}

#endif