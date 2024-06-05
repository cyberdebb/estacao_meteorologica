import requests
import json


def enviar_dados(dados, url):
    headers = {'Content-Type': 'application/json'}
    print(dados)
    response = requests.post(url, data=json.dumps(dados), headers=headers)
    print(response.status_code, response.text)
    #return response.status_code, response.text

 
post_data = '{"data": "19:48:46 01/06/2024", "temperatura": 18.6, "umidade": 87 }'

dados = json.loads(post_data)  # Tenta analisar a string como JSON

#url = "https://estacao-meteorologica-im7c10its-ludmilas-projects-fb4d1943.vercel.app/dht"
url = "https://estacao-meteorologica.vercel.app/dht"

enviar_dados(dados, url)      
            