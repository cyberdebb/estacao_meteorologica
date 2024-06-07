#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <ArduinoJson.h> // Inclua a biblioteca ArduinoJson
#include <time.h>

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

void get_current_datetime(char* buffer, size_t buffer_size) {
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(buffer, buffer_size, "%H:%M:%S %d/%m/%Y", tm_info);
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
    //http.begin("http://192.168.0.106:8080"); // Substitua pelo IP do seu computador
    http.addHeader("Content-Type", "application/json");

    char json_buffer[100];
    char datetime[20];
    get_current_datetime(datetime, sizeof(datetime));

    char temp_str[6];  // "xx.xx" + null terminator
    char humidity_str[6];  // "xx.xx" + null terminator

    // Formatação dos valores
    read_dht_temp(temp_str);
    read_dht_humidity(humidity_str);

    // Formatação do JSON
    snprintf(json_buffer, sizeof(json_buffer), "{\"data\": \"%s\", \"temperatura\": \"%s\", \"umidade\": \"%s\"}",  datetime, temp_str, humidity_str);

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
  delay(10000); // Envia a cada 10 segundos
}

