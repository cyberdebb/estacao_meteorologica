#ifndef PLUVIOMETER_H
#define PLUVIOMETER_H

#define DIAMETRO 125 // diametro interno do balde
#define RAIO 6.25 // raio interno do balde
#define VOLUME 3.05 // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

#include "../sensor.h"
#include <WiFi.h>

const char* ssid = "Cowork-Extensao"; // "SUA_REDE_WIFI"
const char* password = "extensaocts"; // "SUA_SENHA"


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
    String getSensorData() override;
    ~PluviometerSensor();
};

PluviometerSensor::PluviometerSensor() {}

void PluviometerSensor::getData() {
  // float area_recipiente = 3.14159265 * (RAIO * RAIO); // área da seção transversal do recipiente em cm²
  // float volume_por_virada = (VOLUME/area_recipiente);
  volume_coletado = (REEDCOUNT * 0.25) * 10; // volume total coletado em cm³
}

String PluviometerSensor::getSensorData() {
  getData();

  char buffer[100];
  //snprintf(buffer, sizeof(buffer), "Viradas: %lu\nChuva: %.2f mm", REEDCOUNT, volume_coletado);
  int idStation = 1;
  
  snprintf(buffer, sizeof(buffer),
         "{\"idStation\": \"%d\", \"rainfall\": \"%.2f\" }",
         idStation,volume_coletado );


   //--------------------------------------------------------------------------------------

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
    http.begin("https://estacao-meteorologica.vercel.app/pluviometer");  
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

  // --------------------------------------
             
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