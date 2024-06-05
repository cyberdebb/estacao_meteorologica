#ifndef PLUVIOMETER_H
#define PLUVIOMETER_H

#define DIAMETRO 125 // diametro interno do balde
#define RAIO 6.25 // raio interno do balde
#define VOLUME 3.05 // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

#include "sensor.h"

// Pluviometer sensor class
class PluviometerSensor : public Sensor {
  private:
    int val = 0;
    int old_val = 0;
    float volume_coletado = 0;
    
  public:
    static volatile unsigned long ContactBounce;
    static volatile unsigned long REEDCOUNT;

    PluviometerSensor();
    void getData();
    String getJsonData() override;
    String getSensorData() override;
    ~PluviometerSensor();
};

PluviometerSensor::PluviometerSensor() {}

void PluviometerSensor::getData() {
  // float area_recipiente = 3.14159265 * (RAIO * RAIO); // área da seção transversal do recipiente em cm²
  // float volume_por_virada = (VOLUME/area_recipiente);
  volume_coletado = (REEDCOUNT * 0.25) * 10; // volume total coletado em cm³
}

String PluviometerSensor::getJsonData() {
  getData();

  DynamicJsonDocument doc(256);
  doc["volume"] = volume_coletado;

  String jsonData;
  serializeJson(doc, jsonData);

  return jsonData;
}

String PluviometerSensor::getSensorData() {
  getData();

  char buffer[100];
  snprintf(buffer, sizeof(buffer), "Viradas: %lu\nChuva: %.2f mm", REEDCOUNT, volume_coletado);
  return String(buffer);
}

PluviometerSensor::~PluviometerSensor() {}

// Defining static interruption variables
volatile unsigned long PluviometerSensor::ContactBounce = 0;
volatile unsigned long PluviometerSensor::REEDCOUNT = 0;

// Pluviometer Interruption function
static void IRAM_ATTR isr_rain() { // This is the function that the interrupt calls to increment the turning count
  if ((millis() - PluviometerSensor::ContactBounce) > 50) { // debounce the switch contact.
    PluviometerSensor::REEDCOUNT++; // Incrementa a contagem de pulsos
    PluviometerSensor::ContactBounce = millis();
  }
}

#endif