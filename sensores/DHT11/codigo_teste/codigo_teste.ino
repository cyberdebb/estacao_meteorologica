#include <DHT.h>

DHT dht(15,DHT11);

void setup() {
  // put your setup code here, to run once:
 dht.begin();
 delay(2000);

 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 float temp = dht.readTemperature();
 float umidade = dht.readHumidity();

 Serial.print("TEMP C ");
 Serial.print(temp);

 Serial.print(" -- Umidade ");
 Serial.print(umidade);
 Serial.println(" % ");
 delay(2000);
}