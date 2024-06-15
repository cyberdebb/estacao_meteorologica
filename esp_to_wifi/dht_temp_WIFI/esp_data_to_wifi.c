#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>



const char* ssid = "Starlink"; // "SUA_REDE_WIFI"
const char* password = "diversao"; // "SUA_SENHA"

DHT dht(26,DHT11);


void read_dht_temp(char* temp_str) {
    float temp = dht.readTemperature();
    dtostrf(temp, 4, 2, temp_str);
}

void read_dht_humidity(char* humidity_str) {
    float humidity = dht.readHumidity();
    dtostrf(humidity, 4, 2, humidity_str);
}




void setup() {

  dht.begin();
  delay(2000);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://estacao-meteorologica.vercel.app/dht");  
    
    http.addHeader("Content-Type", "application/json");

    char json_buffer[100];   
    char temp_str[6];  
    char humidity_str[6];  

    read_dht_temp(temp_str);
    read_dht_humidity(humidity_str);
    

    // Formatação do JSON
     snprintf(json_buffer, sizeof(json_buffer), "{\"idStation\": \"0\", \"temperatura\": \"%s\", \"umidade\": \"%s\"}", temp_str, humidity_str);

    Serial.println(json_buffer);
    
    
    int httpResponseCode = http.POST(json_buffer);

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
  delay(10000); // Envia a cada 10 segundos
}

