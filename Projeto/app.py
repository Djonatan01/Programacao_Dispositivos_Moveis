import requests
import time

def atualiza_dados():  
    time.sleep(1)
    url = 'http://192.168.1.8'
    try:
        response = requests.get(url)
    except requests.exceptions.ConnectionError as e:
        lista = str(e).split("BadStatusLine")
        texto = str(lista[1]).split("'")
        print("Cartão lido foi: " + texto[1])

atualiza_dados()




    


