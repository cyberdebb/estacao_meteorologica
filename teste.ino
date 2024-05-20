// integração bmp e dht

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// Define the DHT sensor and its pin
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Define the BMP sensor and its pin
#define BMP_SDA 21
#define BMP_SCL 22

// Define the I2C address and initialize the BMP280 object
Adafruit_BMP280 bmp; // I2C

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  while (!Serial) delay(100);   // Wait for native USB

  // Initialize the BMP280 sensor
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or try a different address!"));
    while (1) delay(10);  // Loop forever if sensor initialization fails
  }

  // Initialize the DHT11 sensor
  dht.begin();
  
  // Default settings for BMP280 from datasheet
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  // Read temperature and pressure from BMP280
  float bmp_temp = bmp.readTemperature();
  float pressure = bmp.readPressure();

  // Read temperature and humidity from DHT11
  float dht_temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print BMP280 readings to the serial monitor
  Serial.print("BMP280 - TEMP C: ");
  Serial.print(bmp_temp);
  Serial.print(" -- Pressure: ");
  Serial.print(pressure);
  Serial.println(" Pa");

  // Print DHT11 readings to the serial monitor
  Serial.print("DHT11 - TEMP C: ");
  Serial.print(dht_temp);
  Serial.print(" -- Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Optional: Read and print altitude from BMP280
  Serial.print("Approx altitude = ");
  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
  Serial.println(" m");

  // Delay between readings
  delay(2000);
}
