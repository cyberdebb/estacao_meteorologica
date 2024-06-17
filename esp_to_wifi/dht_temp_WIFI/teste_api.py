import requests
import json


def enviar_dados(dados, url):
    headers = {'Content-Type': 'application/json'}
    print(dados)
    response = requests.post(url, data=json.dumps(dados), headers=headers)
    print(response.status_code, response.text)
    #return response.status_code, response.text

"""export const anemometerSchema = joi.object({
    windSpeed: joi.number().required(),
    windDirection: joi.string().required().trim(),
    windAngle: joi.number().required(),
    idStation: joi.string().required().trim(),
});"""
 
 
##dht
post_data = '{"idStation": "1", "temperature": "19.60", "humidity": "87.00"}'
url = "https://estacao-meteorologica.vercel.app/dht"

##pluviometer
#post_data = '{"idStation": "1", "rainfall": "10.50" }'
#url = "https://estacao-meteorologica.vercel.app/pluviometer"

##bmp
#post_data = '{  "idStation": "1" , "pressure": "1013.25", "temperature": "25.5", "altitude": "150.0"  }'
#url = "https://estacao-meteorologica.vercel.app/bmp"

##anemometer
#post_data = '{"idStation": "1", "windSpeed": "5.50", "windDirection": "N", "windAngle": "2.0" }'
#url = "https://estacao-meteorologica.vercel.app/anemometer"

dados = json.loads(post_data)  # Tenta analisar a string como JSON



enviar_dados(dados, url)      
print(type(dados))

# hivern
# mqtt-client.empx
# text.mosquito
