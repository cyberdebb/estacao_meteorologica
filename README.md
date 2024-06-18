# Estação Metereológica
## 1. Introdução

Este projeto visa desenvolver uma solução integrada para o monitoramento de condições meteorológicas, utilizando tecnologias de ponta em hardware e comunicações. Neste repositório, focaremos exclusivamente na montagem do hardware e na integração do sistema embarcado com um servidor remoto, detalhando cada componente usado, sua configuração e a interconexão necessária para a transmissão eficiente de dados.

Para aqueles interessados na implementação completa, incluindo o servidor, interfaces de usuário, backend, e banco de dados, esses aspectos são abordados em um repositório separado. Essa divisão permite uma especialização mais aprofundada em cada área e facilita o gerenciamento e a colaboração no desenvolvimento do projeto.

## Participantes 
- Augusto Daleffe
- Ludmila Silveira
- Débora Castro
- Eduardo Swarowsky
- Vinicius Muchulski

### Diagrama de comunicação
![diagrama_de_comunicacao](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/a105d673-0c97-417b-b6c3-62494302f3ab)

[Link para o repositório](https://github.com/Ludmilahttps/EstacaoMeteorologica)

## 2. Materiais e métodos 

> Nota: Neste projeto, não foi utilizado o sensor de temperatura e pressão BMP280 por problemas na utilização do material. Porém, o hardware e o software permitem sua utilização para integração na estação meteorológica

Esta seção descreve detalhadamente os componentes e processos utilizados na construção e operação da estação meteorológica. 

### Caracterização do sistema embarcado

- [**ESP32 WROOM**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/ESP32/README.md): Um módulo microcontrolador com Wi-Fi e Bluetooth integrados, ideal para aplicações IoT.
- [**DHT11**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/DHT11/README.md): Sensor de temperatura e umidade, usado para medições ambientais básicas.
- [**Pluviômetro**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/Pluviometro/README.md): Dispositivo utilizado para medir a quantidade de precipitação.
- [**Anemômetro Arduino SV10**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/Anemometro/README.md): Sensor utilizado para medir a velocidade do vento.
- [**Indicador de direção do vento Arduino DV10**](https://github.com/cyberdebb/estacao_meteorologica/blob/main/sensores/Ind_Direcao_Vento/README.md): Sensor utilizado para determinar a direção do vento.

### Diagrama dos componentes

O diagrama abaixo define a configuração física utilizada e a interconexão dos componentes da estação meteorológica: 
![Diagrama PI_Grande](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/c75c16e5-882f-4b96-8760-c9f6ee9439b8)

![Imagem do WhatsApp de 2024-06-15 à(s) 17 48 53_0760c21e](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/a055155b-81d3-48e2-a00d-33777d665640)

### Tutorial de como fazer o esp32 funcionar

#### Instalação do Driver para o ESP32

1. **Baixe e Instale o Driver:**

    - Antes de conectar o ESP32 ao seu computador, é necessário instalar o driver adequado para garantir que o dispositivo seja reconhecido corretamente. Você pode encontrar o driver específico para o ESP32 no seguinte link: [Instalação do Driver para ESP32 - RoboCore](https://www.robocore.net/tutoriais/instalando-driver-do-nodemcu)
    - Siga as instruções no site para baixar e instalar o driver correspondente ao seu sistema operacional.

2. **Conectar o ESP32 ao Computador:**

    - Após a instalação do driver, conecte o ESP32 ao computador usando um cabo USB. Se tudo estiver correto, o dispositivo deverá ser reconhecido e uma nova porta COM será listada no seu sistema.

#### Configuração no Arduino IDE

3. **Instale o Arduino IDE:**

    - Se ainda não instalou, baixe e instale o Arduino IDE diretamente do site oficial: [Arduino - Software](https://www.arduino.cc/en/software)

4. **Adicione a URL de Gerenciamento de Placas do ESP32:**

    - Abra o Arduino IDE.
    - Vá em **Arquivo > Preferências**.
    - No campo "URLs Adicionais de Gerenciadores de Placas", adicione a seguinte URL para permitir a instalação do pacote do ESP32:

		```
		https://dl.espressif.com/dl/package_esp32_index.json
		```

5. **Instale o Pacote do ESP32:**

    - Acesse **Ferramentas > Placa: > Gerenciador de Placas**.
    - Na barra de pesquisa, digite "ESP32".
    - Localize "esp32 by Espressif Systems" e clique em "Instalar".

6. **Selecionar a Placa ESP32 e a Porta COM:**

    - Após a instalação do pacote, vá em **Ferramentas > Placa** e selecione o modelo do seu ESP32 na lista sob o título "ESP32 Arduino".
    - Vá em **Ferramentas > Porta** e selecione a porta COM que aparece (associada ao ESP32).

### Instalação das bibliotecas necessárias no Arduino IDE

Para instalar todas as bibliotecas necessárias, abra o Arduino IDE, vá em Sketch > Incluir Biblioteca > Gerenciar Bibliotecas, e procure e instale as seguintes bibliotecas:

- Adafruit BMP280 Library by Adafruit
- Adafruit BusIO by Adafruit
- Adafruit Unified Sensor by Adafruit
- ArduinoJson by Benoit
- DHT sensor library by Adafruit

### Descrição dos Problemas e Soluções 

#### Problemas com a memória flash do esp32

**Descrição do Problema:** Às vezes, pode ser necessário apagar a memória flash do ESP32 para resolver problemas de estabilidade ou falhas ao carregar novos programas. Esse procedimento torna-se essencial especialmente se o botão de reset físico (RST) não estiver funcionando, impedindo um reinício suave do dispositivo.

**Solução:**

1. **Instalar a Biblioteca esptool:** O esptool é uma ferramenta em linha de comando que permite a comunicação com o chipset ESP para apagar ou gravar a memória flash.

	 - Instale o esptool usando o pip, o gerenciador de pacotes Python:

		```
		 pip install esptool
		```  

2. **Apagar a Memória Flash:** Para apagar completamente a memória flash do ESP32, siga os passos abaixo. Este processo é útil para limpar configurações antigas que podem estar causando conflitos.

    - Abra o terminal ou prompt de comando.
    - Execute o seguinte comando para apagar a memória flash:

		```
		python -m esptool --chip esp32 erase_flash
		```

3. **Verificação de Sucesso:**

    - Após apagar a memória flash, reconecte o ESP32 ao seu computador e tente carregar um novo programa. Se o programa carregar e executar corretamente, isso indica que a memória foi apagada com sucesso.

### Foto da montagem física
![IMG_2254](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/c5bda040-61ea-4b4f-9dab-8303a7e4922a)

### Vídeo do sistema funcionando
Este vídeo demonstra a operação da estação meteorológica, enfocando a coleta e o registro de dados em tempo real:
https://youtu.be/Y84vYU7VSpE

## 3. Resultados

### Orçamento
O levantamento dos preços de cada componente foi realizado através de pesquisa na internet, consultando sites especializados na venda de componentes eletrônicos como: Amazon, Eletrogate e Usinainfo. Como referência, o orçamento foi levantado em junho/2024. Todos os componentes utilizados na construção da estação e descritos na subseção de caracterização do sistema embarcado estão compilados na tabela:

| Componente                                                                           | Preço    | Fonte      |
| ------------------------------------------------------------------------------------ | -------- | ---------- |
| ESP32 WROOM                                                                          | R$49.90  | Amazon     |
| DHT11                                                                                | R$10.36  | Eletrogate |
| BMP280                                                                               | R$7.50   | Eletrogate |
| Anemômetro Arduino + Indicador de Direção do Vento para Estação Meteorológica SVDV10 | R$749.55 | Usinainfo  |

### Análise de resultados
A seguir, será apresentada uma análise detalhada dos dados coletados pela estação meteorológica. Os resultados são fundamentais para validar a precisão e a eficácia do sistema em monitorar variáveis ambientais críticas, como temperatura, umidade, pressão atmosférica, velocidade e direção do vento, bem como precipitação. A seguir, exploramos os dados obtidos, comparando-os com padrões meteorológicos conhecidos e medições de referência para avaliar a confiabilidade do sistema.
