//Incluir a biblioteca que esta na pasta ZIP junto com o projeto
#include <MySQL_Cursor.h>
#include <MySQL_Connection.h>
//***************************************************
#include <WiFi.h>
//#include <WiFiClientSecure.h>
//Incluindo o sistema de senhas do sistema RFID
#include "arduino_secrets.h"

//Incluindo o servidor do banco de dados
IPAddress server_addr(85,10,205,173);

//Criar a veriavel para gravar no banco de dados
char INSERT_SQL[] = "INSERT INTO djonatanrfid.cartaoRFID (idCartao, descCartao) VALUES ('%d', '%d')";
// Instanciando objetos
WiFiClient client;
MySQL_Connection conn((Client *)&client);
WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    
    delay(10);

    // Estabelecendo conexão com a internet
    WiFi.begin(SECRET_SSID, SECRET_password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    //IP conectado
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
    
    while(!conn.connect(server_addr, 3306, SECRET_USERDB, SECRET_PASSDB)){
        Serial.println("Conexão falhou");
        conn.close();
        delay(1000);
        Serial.println("Conectando SQL novamente...");
      }
      Serial.println("Conectado ao servidor SQL.");
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
            client.print("DC022607");
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
