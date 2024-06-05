#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <ArduinoJson.h> // Inclua a biblioteca ArduinoJson

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
    http.begin("http://192.168.0.106:8080");  // Substitua pelo IP do seu computador
    //http.begin("https://estacao-meteorologica-im7c10its-ludmilas-projects-fb4d1943.vercel.app/post/dht");
    http.addHeader("Content-Type", "application/json");

    float temp = dht.readTemperature();
    float umidade = dht.readHumidity();

    //String data = "Este é o dado que quero enviar";
    //data = "TEMP C " + String(temp) + " -- Umidade " + String(umidade) + " %" ;

     // Cria o objeto JSON
    DynamicJsonDocument doc(1024); // Ajuste o tamanho conforme necessário
    doc["temperatura"] = temp;
    doc["umidade"] = umidade;

    String jsonData;
    serializeJson(doc, jsonData);
    
    int httpResponseCode = http.POST(jsonData);

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
  delay(10000); // Envia a cada 5 segundos
}
