#ifndef SENSORS_H
#define SENSORS_H

#include <iostream>
#include <string>
#include <sstream>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

// Pluviometer constants
#define DIAMETRO 125 // diametro interno do balde
#define RAIO 6.25 // raio interno do balde
#define VOLUME 3.05 // volume da bascula (em cm3) (1cm3 == 1ml) (1ml == 1000mm3)

// Anemometer constants
#define PERIOD 5000 // Measurement period in milliseconds
#define RADIUS 147 // Anemometer radius in mm

class DhtSensor {
  private:
    DHT dht;
    float temp = 0;
    float umidade = 0;

  public: 
    DhtSensor(uint8_t pin, uint8_t type) : dht(pin, type) {}

    void begin() {
      dht.begin();
    }

    std::string getDht() {
      temp = dht.readTemperature();
      umidade = dht.readHumidity();

      std::string data = "TEMP C " + std::to_string(temp) + " -- Umidade " + std::to_string(umidade) + " % ";

      Serial.println(data.c_str());  // Usando c_str() para converter std::string para const char* que é necessário para Serial.println
      return data;
    }
};

class BmpSensor {
  private:
    Adafruit_BMP280 bmp;
    float temperature = 0;
    float pressure = 0;
    float altitude = 0;

  public:
    bool begin(uint8_t address) {
      return bmp.begin(address); 
    }

    uint8_t sensorID() {
      return bmp.sensorID();
    }
    
    void setSampling(Adafruit_BMP280::sensor_mode mode, Adafruit_BMP280::sensor_sampling tempSampling, Adafruit_BMP280::sensor_sampling pressSampling, Adafruit_BMP280::sensor_filter filter, Adafruit_BMP280::standby_duration duration) {
      bmp.setSampling(mode, tempSampling, pressSampling, filter, duration);
    }

    std::string getBmp() {
      temperature = bmp.readTemperature();
      pressure = bmp.readPressure();
      altitude = bmp.readAltitude(1011);

      std::string data = "Temperature = " + std::to_string(temperature) + " *C\n" +
                     "Pressure = " + std::to_string(pressure) + " Pa\n" +
                     "Approx altitude = " + std::to_string(altitude) + " m\n";

      Serial.println(data.c_str()); 
      return data;
    }
};

class PluviometerSensor {
  private:
    int val = 0;
    int old_val = 0;
    float volume_coletado = 0;
    
  public:
    static volatile unsigned long ContactBounce;
    static volatile unsigned long REEDCOUNT;

    std::string getRain(){
      // float area_recipiente = 3.14159265 * (RAIO * RAIO); // área da seção transversal do recipiente em cm²
      // float volume_por_virada = (VOLUME/area_recipiente);
      volume_coletado = (REEDCOUNT * 0.25) * 10; // volume total coletado em cm³

      std::string data = "Viradas: " + std::to_string(REEDCOUNT) + "\n" +
                     "Chuva: " + std::to_string(volume_coletado) + " mm\n";

      Serial.println(data.c_str());  // Imprime a string composta de uma só vez
      return data;
    }
};

class AnemometerSensor {
  private:
    unsigned int rpm = 0;  // Revolutions per minute
    float windSpeedMetersPerSecond = 0;  // Wind speed in m/s
    float windSpeedKilometersPerHour = 0;  // Wind speed in km/h

  public:
    static volatile unsigned int counter; // Magnet counter for sensor

    void measureWindSpeed() {
      counter = 0;  
      long startTime = millis();
      while (millis() < startTime + PERIOD) {}; // Wait for the period to complete
    }

    void calculateRPM() {
      rpm = (counter * 60) / (PERIOD / 1000); // Calculate RPM
    }

    void calculateWindSpeedMetersPerSecond() {
      windSpeedMetersPerSecond = ((4 * PI * RADIUS * rpm) / 60) / 1000; // Calculate wind speed in m/s
    }

    void calculateWindSpeedKilometersPerHour() {
      windSpeedKilometersPerHour = windSpeedMetersPerSecond * 3.6; // Convert m/s to km/h
    }

    std::string getAnemometer() {
      measureWindSpeed();
      calculateRPM();
      calculateWindSpeedMetersPerSecond();
      calculateWindSpeedKilometersPerHour();

      std::string data = "Counter: " + std::to_string(counter) + 
                         "; RPM: " + std::to_string(rpm) + 
                         "; Wind speed: " + std::to_string(windSpeedMetersPerSecond) + 
                         " [m/s] " + std::to_string(windSpeedKilometersPerHour) + " [km/h]\n";

      Serial.println(data.c_str());  
      return data;
    }
};

class WindIndicatorSensor {
  private:
    int Winddir = 0; // Declara o valor inicial em 0
    float valor = 0; // declara a variável inicial em 0
    int pin;

  public:
    WindIndicatorSensor(int win_pin) : pin(win_pin) {}

    std::string getWindDirection() {
      valor = analogRead(pin) * (5.0 / 4095.0); // Calcula a tensão para ESP32, onde a resolução ADC é 12-bit (0-4095) e a referência é 5V

      std::string windDirection;

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

      char buffer[50];
      snprintf(buffer, sizeof(buffer), "%.2f volt", valor);
      std::string data = "Leitura do sensor: " + std::string(buffer) + "\nDireção do Vento: " + windDirection + "\nÂngulo: " + std::to_string(Winddir) + " Graus";

      Serial.println(data.c_str()); 
      return data;
    }
};

// Defining static interruption variables
volatile unsigned int AnemometerSensor::counter = 0;
volatile unsigned long PluviometerSensor::ContactBounce = 0;
volatile unsigned long PluviometerSensor::REEDCOUNT = 0;

// Pluviometer Interruption function
static void IRAM_ATTR isr_rain() { // This is the function that the interrupt calls to increment the turning count
  if ((millis() - PluviometerSensor::ContactBounce) > 50) { // debounce the switch contact.
    PluviometerSensor::REEDCOUNT++; // Incrementa a contagem de pulsos
    PluviometerSensor::ContactBounce = millis();
  }
}

// Anemometer Interruption function
static void countRevolution() {
  AnemometerSensor::counter++; // Increment counter for each revolution detected
}

#endif