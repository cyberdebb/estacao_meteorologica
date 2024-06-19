# ESP32 WROOM
![image-removebg-preview (1)](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/9e9e1087-d345-4934-84ed-f355491677b7)

O [ESP32 DevKit V1](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf) é uma placa de desenvolvimento avançada que oferece um conjunto rico de recursos, tornando-a uma excelente escolha para uma variedade de aplicações que requerem capacidades sem fio, baixo consumo de energia e recursos avançados de conectividade. Aqui está uma visão geral destacando suas principais capacidades e especificações técnicas:

### Principais Recursos

- **Integração de Componentes RF**: O ESP32 já inclui antena integrada e balun de RF, amplificador de potência, amplificadores de baixo ruído, filtros e módulo de gerenciamento de energia. A solução completa ocupa o mínimo espaço possível na placa de circuito impresso.

- **Tecnologia de Baixo Consumo**: Utiliza chips Wi-Fi e Bluetooth de modo duplo 2,4 GHz, fabricados pela TSMC com tecnologia de 40 nm, oferecendo as melhores propriedades de potência e RF, o que garante segurança, confiabilidade e escalabilidade para uma variedade de aplicações.

### Layout do Flash
- **Organização do Flash Interno**: O flash interno do módulo ESP32 é organizado em uma única área de flash com páginas de 4096 bytes cada. O flash começa no endereço 0x00000, mas muitas áreas são reservadas para o SDK Esp32 IDF. Existem dois layouts diferentes, dependendo da presença de suporte a BLE.

### Energia
- **Fonte de Alimentação**: A energia para o Esp32 DevKit v1 é fornecida via conector USB Micro B a bordo ou diretamente pelo pino "VIN". A fonte de energia é selecionada automaticamente.

- **Faixa de Tensão Externa**: O dispositivo pode operar com uma fonte de alimentação externa de 6 a 20 volts. Se utilizar mais de 12V, o regulador de tensão pode superaquecer e danificar o dispositivo. A faixa recomendada é de 7 a 12 volts.

### Conectar, Registrar, Virtualizar e Programar
- **Chip de Serial para USB**: O Esp32 DevKit v1 vem com um chip de serial para USB a bordo que permite programar e abrir o UART do módulo ESP32. Dependendo do seu sistema (Mac ou Windows), podem ser necessários drivers que podem ser baixados da página oficial de documentação da Espressif. Em sistemas Linux, o DevKit v1 deve funcionar imediatamente.

![image](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/b46d96a6-a364-44a7-8699-3bbed1ecb281)

## Especificações
| INFORMAÇÃO                          | ESP32                                         |
|-------------------------------------|-----------------------------------------------|
| PROCESSADOR                         | Tensilica 32-bit Single-/Dual-core CPU Xtensa LX6 |
| TENSÃO DE OPERAÇÃO                  | 3.3V                                          |
| TENSÃO DE ENTRADA                   | 7-12V                                         |
| PINOS DE I/O DIGITAL (DIO)          | 25                                            |
| PINOS DE ENTRADA ANALÓGICA (ADC)    | 6                                             |
| PINOS DE SAÍDA ANALÓGICA (DAC)      | 2                                             |
| UARTs                               | 3                                             |
| SPIs                                | 2                                             |
| I2Cs                                | 3                                             |
| MEMÓRIA FLASH                       | 4 MB                                          |
| MEMÓRIA SRAM                        | 520 KB                                        |
| VELOCIDADE DO CLOCK                 | 240 MHz                                       |
| WI-FI                               | IEEE 802.11 b/g/n/e/i                         |
| CARACTERÍSTICAS DE WI-FI            | Integrated TR switch, balun, LNA, power amplifier and matching network |
| SEGURANÇA WI-FI                     | WEP or WPA/WPA2 authentication, or open networks |
| DIMENSÕES                           | 51.5x29x5mm                                   |
