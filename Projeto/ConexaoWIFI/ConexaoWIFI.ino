#include <WiFi.h>
//nome da rede a ser utilizada
const char* ssid     = "DIEGO";
//Senha da rede
const char* password = "@1c14A6CA6";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    
    delay(10);

    // Estabelecendo conexão com a internet
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    //IP conectado
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

void loop(){

 WiFiClient client = server.available();   // Lendo informações envidas pelo navegador

  if (client) {                                     
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                  
        if (c == '\n') {                   
          if (currentLine.length() == 0) {
            //enviar as informações do cartão RFID que foi lido
            client.print("Dados do cartão lido");
            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }
      }
    }
    // Encerrando a conexão
    client.stop();
  }
}
