import serial
from datetime import datetime
import re


# Substitua 'COM3' pela porta serial do seu ESP32
serial_port = 'COM4'
baud_rate = 115200
nome_arquivo = 'dados_sensor.csv'

ser = serial.Serial(serial_port, baud_rate)

while True:
    line = ser.readline().decode('utf-8').strip()
   
    now = datetime.now()
    horario = now.strftime("%H:%M:%S %d/%m/%Y")
    
    match = re.search(r"TEMP C (\d+\.\d+) -- Umidade (\d+\.\d+) %", line)
    
    if match:
        temperatura = match.group(1)
        umidade = match.group(2)
        print(temperatura)
        print(umidade)
    
    """temp = str(line).find("C")+1
    temperatura = line[temp:5]
    print(temperatura)
    
    umidade = str(line).find("Umidade")+7
    umid = line[umidade:5]
    print(umid)"""
    
    #temp, umidade = line.split(',')
    #print(f"Temperatura: {temp}°C, Umidade: {umidade}%")
    linha_completa = f"{horario}, {line}"
    
    
    print(linha_completa)
    with open(nome_arquivo, 'a') as f:
        f.write(linha_completa + '\n')
        
        
#ser.close()