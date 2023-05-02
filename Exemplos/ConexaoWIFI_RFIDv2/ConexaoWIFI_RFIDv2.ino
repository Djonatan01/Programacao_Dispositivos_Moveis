#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   22    
#define SS_PIN    21    

String content= "";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}

MFRC522::MIFARE_Key key;

//nome da rede a ser utilizada
//const char* ssid     = "DIEGO";
//Senha da rede
//const char* password = "@1c14A6CA6";

//nome da rede a ser utilizada
const char* ssid     = "mariah";
//Senha da rede
const char* password = "@mariah2012";


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
String cartaoRFID(){
  while (!Serial);     
    SPI.begin();         
    mfrc522.PCD_Init();  

    for (byte i = 0; i < 6; i++) {
      key.keyByte[i] = 0xFF;
    }
    if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
      delay(50);
      return "";
    }
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
    } 
    content.toUpperCase();
    return content;
}
void loop(){
  
  if (content != ""){
    Serial.println(content);
    servidorWEB(content);
  }

content="";
}

String servidorWEB(String cartao){
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
              if (cartao == ""){
                client.print("");
              }else{
                client.print(cartao);
              }
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
