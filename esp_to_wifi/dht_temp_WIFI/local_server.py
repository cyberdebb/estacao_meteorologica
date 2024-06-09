from http.server import BaseHTTPRequestHandler, HTTPServer

import requests
import json
from time import sleep

nome_arquivo = 'dados_sensor.csv'
arquivo_json = 'dados_sensor.json'


"""
Windows
Prompt de Comando (CMD)
Abra o Prompt de Comando: Pressione Win + R, digite cmd e pressione Enter.
Digite o comando ipconfig e pressione Enter.
Procure pelo adaptador de rede que esta conectado à sua rede (geralmente WiFi ou Ethernet) e encontre o campo "Endereço IPv4". O valor mostrado é o IP do seu PC

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
        #post_data = '{"temperatura": 18.60000038, "umidade": 87, "data": "19:48:46 01/06/2024"}'
        
        try:
            dados = json.loads(post_data)  # Tenta analisar a string como JSON
            print("Dados recebidos:", dados)
            self.send_response(200)
            self.send_header("Content-type", "application/json")  # Define o cabeçalho para JSON
            self.end_headers()
            self.wfile.write(b"Data received")
            dados_atualizados = self.salvar_dados(dados)
            
            #status_code, response_text = enviar_dados(dados_atualizados, "https://estacao-meteorologica-im7c10its-ludmilas-projects-fb4d1943.vercel.app/dht")
                                                                        #https://estacao-meteorologica-im7c10its-ludmilas-projects-fb4d1943.vercel.app/post/dht
            #print(f"Enviado para endpoint remoto: {status_code}, {response_text}")
            
            
        except json.JSONDecodeError:
            print("Erro: Dados recebidos não são um JSON valido.")
            self.send_response(400)  # Bad Request
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(b'Erro: Envie dados JSON validos.')
            return
        
                
    def salvar_dados(self, dados):
        
        
        
        # Extrai dados do JSON
        temp = dados.get('temperatura', 'N/A')
        umidade = dados.get('umidade', 'N/A')
        horario = dados.get('data', 'N/A')
            
   
   
        linha_completa = f"{horario}, {temp}, {umidade}"
        # Abre o arquivo CSV no modo de append ('a') para adicionar dados
        with open(nome_arquivo, 'a') as f:
            f.write(linha_completa + '\n')
        
           
        linha_json = json.dumps(dados)
        #print(linha_json)
        
        with open(arquivo_json, 'a') as fj:
                fj.write(linha_json + '\n')
                
        return dados
        
def enviar_dados(dados, url):
    headers = {'Content-Type': 'application/json'}
    response = requests.post(url, data=json.dumps(dados), headers=headers)
    return response.status_code, response.text
           

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting server on port {port}...')
    httpd.serve_forever()

if __name__ == "__main__":
    
    run()