# ESP32
![image-removebg-preview (1)](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/9e9e1087-d345-4934-84ed-f355491677b7)

O [ESP32 DevKit V1](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf) é uma das placas de desenvolvimento criadas para avaliar o módulo ESP-WROOM-32. Baseia-se no microcontrolador ESP32 que inclui suporte a Wifi, Bluetooth, Ethernet e baixo consumo de energia, tudo em um único chip.

O ESP32 já possui antena integrada e balun RF, amplificador de potência, amplificadores de baixo ruído, filtros e módulo de gestão de energia. A solução completa ocupa a menor quantidade possível de espaço em placa de circuito impresso. Esta placa utiliza chips Wi-Fi e Bluetooth de modo duplo 2.4 GHz da TSMC com tecnologia de baixo consumo de 40nm, oferecendo as melhores propriedades de potência e RF, o que é seguro, confiável e escalável para uma variedade de aplicações.

### Layout do Flash
O flash interno do módulo ESP32 é organizado em uma única área de flash com páginas de 4096 bytes cada. O flash começa no endereço 0x00000, mas muitas áreas são reservadas para o SDK IDF do Esp32. Existem dois layouts diferentes baseados na presença de suporte BLE.

### Energia
A energia para o ESP32 DevKit V1 é fornecida através do conector USB Micro B a bordo ou diretamente pelo pino "VIN". A fonte de energia é selecionada automaticamente.

O dispositivo pode operar com uma fonte de alimentação externa de 6 a 20 volts. Se usar mais de 12V, o regulador de tensão pode superaquecer e danificar o dispositivo. A faixa recomendada é de 7 a 12 volts.

### Conectar, Registrar, Virtualizar e Programar
O ESP32 DevKit V1 vem com um chip serial-para-USB a bordo que permite programar e abrir o UART do módulo ESP32. Dependendo do seu sistema (Mac ou Windows), podem ser necessários drivers que podem ser baixados da página de documentação oficial da Espressif. Em sistemas Linux, o DevKit V1 deve funcionar imediatamente.

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
