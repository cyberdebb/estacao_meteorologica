import serial
from datetime import datetime
import re
import json

# Substitua pela porta serial do seu ESP32
serial_port = 'COM4'
baud_rate = 115200
nome_arquivo = 'dados_sensor.csv'
arquivo_json = 'dados_sensor.json'

ser = serial.Serial(serial_port, baud_rate)

#SE RODAR ESSE CODIGO COM W o arquivo csv é zerado!!
"""Esse bloco de código está comentado, mas se for descomentado, 
ele abrirá o arquivo CSV no modo de escrita ('w'), apagando todo o conteúdo anterior. 
A linha comentada f.write("data,temperatura,umidade\n") adiciona um cabeçalho ao arquivo CSV."""
#with open(nome_arquivo, 'w') as f:
    #f.write("data,temperatura,umidade\n")


# Loop principal do programa
while True:
    line = ser.readline().decode('utf-8').strip()
   
    now = datetime.now()
    horario = now.strftime("%H:%M:%S %d/%m/%Y")
    
    # Utiliza expressão regular para extrair temperatura e umidade da linha
    match = re.search(r"TEMP C (\d+\.\d+) -- Umidade (\d+\.\d+) %", line)
    
    if match:
        temp = match.group(1)
        umidade = match.group(2)
        print(f"Temperatura: {temp}°C, Umidade: {umidade}%")
        
    
    linha_completa = f"{horario}, {temp}, {umidade}"
    print(linha_completa)
    
    
    # Abre o arquivo CSV no modo de append ('a') para adicionar dados
    with open(nome_arquivo, 'a') as f:
        f.write(linha_completa + '\n')
        
    dados = {
            'tempo': horario,
            'temperatura': temp,
            'umidade': umidade
        }
    linha_json = json.dumps(dados)
    print(linha_json)
    
    with open(arquivo_json, 'a') as fj:
            fj.write(linha_json + '\n')
        
#ser.close()