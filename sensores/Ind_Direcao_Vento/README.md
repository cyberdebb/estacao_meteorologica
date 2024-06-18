# Indicador de Direção do Vento Arduino DV10
![image-removebg-preview (5)](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/5addfcc9-ec4f-4d65-b7c1-ada5bca67632)

O Indicador de Direção do Vento é mais um recurso para estação meteorológica, uma ferramenta de verificação climática que possui a capacidade de proporcionar diversos tipos de dados, dentre eles podemos destacar a verificação da velocidade do vento através de um anemômetro e a verificação da quantidade de chuva através de um pluviômetro.

Em muitos projetos estas informações são extremamente importantes, uma vez que podem influenciar em plantações, indicar possíveis acontecimentos climáticos e consequentemente verificar a possibilidade de agir na prevenção de algum dano à plantações, residências e afins.

O Indicador de Direção do Vento DV10 é um produto produzido quase que totalmente produzido em alumínio, com exceção dos locais de instalação dos sensores que são produzidos de maneira a aumentar a sua isolação à interferências externas.

Para auxiliar em seus processos de instalação, por sua vez, o Indicador de Direção possui um exclusivo sistema de fixação para os amis diferenciados modelos de hastes e espessuras. Veja abaixo uma imagem que demonstra o funcionamento do mesmo, um sistema de rosca com porcas:

![image](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/c993cbd7-67a6-452e-bcf8-3362f92fddd9)

Sistema de fixação para suportes e hastes.

O módulo de verificação do Indicador de Direção do Vento possui um diferenciado sistema de verificação que se baseia na variação da sua resistência para indicar a direção à qual o vento sopra. Cada direção está diretamente associada a um resistor de 10K, segundo o esquema elétrico disponível no site Usinainfo, que utiliza um resistor 4K7 em sua conexão, os valores de funcionamento são os seguintes:

![image](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/4f825205-755d-4b9b-b003-d3b23d771006)

Tabela de valores da resistência e direção do vento com resistor 4K7

Como podemos ver na tabela acima e na imagem abaixo, o Sensor de Direção do Vento possui oito Reed Switch ligados a oito resistores de 10K distribuídos em uma ligação em série à qual de acordo com o movimento da hélice soma o valor das resistências e retorna valores diferentes de tensão para verificação analógica.

![image](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/0ca2bc1a-e1a5-4402-a312-2b8f93202c88)

Módulo de Funcionamento do Indicador de Direção do Vento

O acionamento dos Sensores Reed Switch se dão através de um exclusivo imã fixado em uma das peças de deslocamento do Indicador de Direção do Vento, o qual fica responsável por realizar a aproximação das placas que constituem o sensor e interligam os resistores. Veja uma imagem do imã e sua localização:

![image](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/e7b69386-434b-4e62-ae16-ae04ea37a05e)

Sistema de acionamento do Sensor Reed Switch

O sistema de funcionamento do Indicador de Direção do Vento é extremamente simples, de acordo com o deslocamento da pá, varia-se o valor da tensão de saída e consequentemente esta tensão é associada a uma direção através do software no Arduino. Porém vale ficarmos atentos a uma informação bem importante:

![image](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/2e8ad047-bb83-4340-863e-c2f4247f71de)

Indicador de Direção do Vento e Pá de deslocamento

Para quem deseja uma visualização direta da informação de maneira não digital, vale ressaltar os elementos de indicação da direção do vento e a pá de deslocamento, elementos responsáveis por indicar e posicionar o sensor de acordo com o vento que sopra no local de verificação.

## Características
- Pode ser utilizado com outros microcontroladores;  
- Eixo com rolamento lacrado (livre de manutenção);  
- Sensor magnético lacrado;  
- Fácil instalação;  
- Alta precisão;  
- Boa estabilidade;  
- Linearidade de dados;  
- Forte proteção anti-interferência;  
- Abraçadeira para fixação;  
- Proteção contra intempéries;  
- Ideal para estufas, áreas de proteção ambiental monitoradas, estações meteorológicas, portos, áreas agrícolas, entre outros ambientes;

## Especificações
| INFORMAÇÃO                        | Indicador de Direção do Vento Arduino SV10 |
| --------------------------------- | ------------------------------------------ |
| MATERIAL                          | Alumínio e Plástico Resistente             |
| TENSÃO DE TRABALHO                | 5V DC                                      |
| TIPO                              | Analógico                                  |
| MEIO DE TRANSMISSÃO               | cabo                                       |
| TEMPERATURA DE TRABALHO           | -40C ~ 80C                                 |
| COMPRIMENTO DO CABO               | ~5 metros                                  |
| COMPRIMENTO SUPORTE               | 205mm                                      |
| DIÂMETRO MÁXIMO TUBO PARA FIXAÇÃO | 35mm                                       |
| GIRO                              | 360°                                       |
| PRECISÃO                          | ~95%                                       |

## Conexões
| Sensor de Direção do Vento | ESP WROOM 32 | Número Do Pino ESP32 |
|:--------------------------:|:------------:|:--------------------:|
|            VCC             |      5V      |          5V          |
|            GND             |      GND     |          GND         |
|            DAT             |     GPIO     |         GPIO26       |

## Resultados
![Imagem do WhatsApp de 2024-06-18 à(s) 14 12 54_f64e1a8b](https://github.com/cyberdebb/estacao_meteorologica/assets/107296659/805abf03-ba21-4d5a-897c-72530602b2bb)


