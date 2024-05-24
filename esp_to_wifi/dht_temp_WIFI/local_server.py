from http.server import BaseHTTPRequestHandler, HTTPServer

from datetime import datetime
import re
import json

nome_arquivo = 'dados_sensor.csv'
arquivo_json = 'dados_sensor.json'


"""
Windows
Prompt de Comando (CMD)
Abra o Prompt de Comando: Pressione Win + R, digite cmd e pressione Enter.
Digite o comando ipconfig e pressione Enter.
Procure pelo adaptador de rede que está conectado à sua rede (geralmente WiFi ou Ethernet) e encontre o campo "Endereço IPv4". O valor mostrado é o IP do seu PC

"""


class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(b"Server is running")

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        post_data = self.rfile.read(content_length).decode('utf-8')  # Decodifica os dados aqui
        print("Received data:", post_data)
        self.send_response(200)
        self.end_headers()
        self.wfile.write(b"Data received")
        
        self.salvar_dados(post_data)
                
    def salvar_dados(self, dados):
        
        line = dados

        print(f"Received data: {line}")
        
        now = datetime.now()
        horario = now.strftime("%H:%M:%S %d/%m/%Y")
        
        # Utiliza expressão regular para extrair temperatura e umidade da linha
        match = re.search(r"TEMP C (\d+\.\d+) -- Umidade (\d+\.\d+) %", line)
        
        if match:
            temp = match.group(1)
            umidade = match.group(2)
            #print(f"Temperatura: {temp}°C, Umidade: {umidade}%")
            
        
        linha_completa = f"{horario}, {temp}, {umidade}"
        #print(linha_completa)
        
        
        # Abre o arquivo CSV no modo de append ('a') para adicionar dados
        with open(nome_arquivo, 'a') as f:
            f.write(linha_completa + '\n')
            
        dados = {
                'tempo': horario,
                'temperatura': temp,
                'umidade': umidade
            }
        linha_json = json.dumps(dados)
        #print(linha_json)
        
        with open(arquivo_json, 'a') as fj:
                fj.write(linha_json + '\n')
        
            

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting server on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    
    run()