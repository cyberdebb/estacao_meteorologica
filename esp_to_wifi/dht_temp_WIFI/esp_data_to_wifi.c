#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>



const char* ssid = "Starlink"; // "SUA_REDE_WIFI"
const char* password = "diversao"; // "SUA_SENHA"

DHT dht(26,DHT11);

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

    float humidity = dht.readHumidity();
    float temp = dht.readTemperature();
    // Formatação do JSON
    snprintf(json_buffer, sizeof(json_buffer), "{\"idStation\": \"1\", \"temperature\": \"%.2f\", \"humidity\": \"%.2f\"}", temp, humidity);

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

