# ESP32 e Sensor DHT11 para Monitoramento de Temperatura e Umidade

Este projeto consiste em um sistema embarcado com um microcontrolador ESP32 e um sensor DHT11 para monitorar a temperatura e a umidade do ambiente. Os dados coletados pelo sensor são enviados para um servidor local através do protocolo HTTP usando a biblioteca WiFi.h do ESP32.

## Arquivos

### esp_data_to_wifi.c

Este arquivo contém o código que será executado no microcontrolador ESP32. Ele realiza as seguintes tarefas:

1. Inclui as bibliotecas necessárias: `WiFi.h`, `HTTPClient.h` e `DHT.h`.
2. Define as credenciais da rede WiFi à qual o ESP32 se conectará.
3. Inicializa o sensor DHT11 no pino 26.
4. Estabelece conexão com a rede WiFi.
5. Envia os dados de temperatura e umidade coletados pelo sensor DHT11 para um servidor local a cada 10 segundos, utilizando uma requisição HTTP POST.

### local_server.py

Este arquivo contém um servidor local simples em Python que recebe os dados enviados pelo ESP32 e os salva em dois arquivos:

1. `dados_sensor.csv`: Um arquivo CSV com dados separados por vírgula, contendo o horário, a temperatura e a umidade.
2. `dados_sensor.json`: Um arquivo JSON com os mesmos dados, porém em formato JSON.

O servidor é executado na porta 8080 e espera receber requisições HTTP POST com os dados no formato `"TEMP C <temperatura> -- Umidade <umidade> %"`.

## Instruções de Uso

1. Certifique-se de ter o firmware adequado instalado no seu ESP32 e faça as conexões necessárias com o sensor DHT11.
2. Atualize o código `esp_data_to_wifi.c` com as credenciais corretas da sua rede WiFi.
3. Faça o upload do código `esp_data_to_wifi.c` para o ESP32.
4. Execute o script `local_server.py` em seu computador local.
5. Certifique-se de que o ESP32 e o computador local estejam na mesma rede WiFi.
6. O ESP32 enviará os dados de temperatura e umidade para o servidor local a cada 10 segundos.
7. Os dados serão salvos nos arquivos `dados_sensor.csv` e `dados_sensor.json`.

Esse sistema pode ser útil para monitorar as condições ambientais em tempo real e registrar os dados para análise posterior.