#ifndef WINDINDICATOR_H
#define WINDINDICATOR_H

#include "../sensor.h"
#include "anemometer.h"

// Wind Indicator DV10 Arduino sensor class
class WindIndicatorSensor : public Sensor {
  private:
    int pin;
    int Winddir = 0; // Declara o valor inicial em 0
    float valor = 0; // declara a variável inicial em 0
    String windDirection;
    AnemometerSensor ane;

  public:
    WindIndicatorSensor(int win_pin);
    void getData();
    String getSensorData() override;
    String sendSensorData() override;
    ~WindIndicatorSensor();
};

WindIndicatorSensor::WindIndicatorSensor(int win_pin) : pin(win_pin) {}

void WindIndicatorSensor::getData() {
  valor = analogRead(pin) * (5.0 / 4095.0); // Calcula a tensão para ESP32, onde a resolução ADC é 12-bit (0-4095) e a referência é 5V

  // Determina a direção do vento baseada na tensão
  if ((valor > 2.4 && valor <= 2.5) || (valor >= 0 && valor <= 0.16)) {
    Winddir = 0;
    windDirection = "Norte";
  } else if (valor > 0.16 && valor <= 0.48) {
    Winddir = 315;
    windDirection = "Noroeste";
  } else if (valor > 0.48 && valor <= 0.80) {
    Winddir = 270;
    windDirection = "Oeste";
  } else if (valor > 0.80 && valor <= 1.12) {
    Winddir = 225;
    windDirection = "Sudoeste";
  } else if (valor > 1.12 && valor <= 1.44) {
    Winddir = 180;
    windDirection = "Sul";
  } else if (valor > 1.44 && valor <= 1.76) {
    Winddir = 135;
    windDirection = "Sudeste";
  } else if (valor > 1.76 && valor <= 2.1) {
    Winddir = 90;
    windDirection = "Leste";
  } else if (valor > 2.1 && valor <= 2.4) {
    Winddir = 45;
    windDirection = "Nordeste";
  } else {
    Winddir = 000;  // Default to 0 if direction is indeterminate
    windDirection = "Indeterminada";
  }
}

// Testing sensors locally
String WindIndicatorSensor::getSensorData() {
  getData();

  char buffer[200];
  snprintf(buffer, sizeof(buffer), "Leitura do sensor: %.2f volt\nDireção do Vento: %s\nÂngulo: %d Graus", valor, windDirection.c_str(), Winddir);

  return String(buffer);
}

// Send data to web server
String WindIndicatorSensor::sendSensorData() {
  getData();

  char buffer[200];
  int idStation = 1;

  snprintf(buffer, sizeof(buffer),
         "{\"idStation\": \"%d\", \"windSpeed\": \"%.2f\", \"windDirection\": \"%s\", \"windAngle\": \"%.1f\"}",
         idStation, ane.getSpeed(), windDirection.c_str(), Winddir);

  sendData("anemometer", String(buffer));
  return String(buffer);
}

WindIndicatorSensor::~WindIndicatorSensor() {}

#endif