import requests
import json


def enviar_dados(dados, url):
    headers = {'Content-Type': 'application/json'}
    response = requests.post(url, data=json.dumps(dados), headers=headers)
    print(response.status_code, response.text)
    #return response.status_code, response.text

 
post_data = '{"temperatura": 18.6, "umidade": 87, "data": "19:48:46 01/06/2024"}'

dados = json.loads(post_data)  # Tenta analisar a string como JSON
print("Dados recebidos:", dados)

url = "https://estacao-meteorologica-im7c10its-ludmilas-projects-fb4d1943.vercel.app/dht"


enviar_dados(dados, url)      
            