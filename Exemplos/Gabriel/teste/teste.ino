#include <WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

//Bliblioteca que adiciona o SQLite (Lembrando que tem que pesquisar ela no SKETCH)
#include <SQLite3.h>


#define RST_PIN   22    
#define SS_PIN    21    

String content= "";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

/* Set your new UID here! */
#define NEW_UID {0xDE, 0xAD, 0xBE, 0xEF}

MFRC522::MIFARE_Key key;

//nome da rede a ser utilizada
const char* ssid     = "DIEGO";
//Senha da rede
const char* password = "@1c14A6CA6";

WiFiServer server(80);

SQLite3 db;

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


    //Puxa o diretório onde o BD ta salvo pra abrir ele
    db.open("/pasta onde vai salvar o arquivo do banco/dbRFID.db");
    //Cria a tabela para armazenar as informações do cartão RFID
    db.exec("CREATE TABLE IF NOT EXISTS dados(id INTEGER PRIMARY KEY AUTOINCREMENT, data_hora TEXT, numCard TEXT)");


}

String testeFunc(String cartaoRFID){


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
            client.print("");
            client.print(cartaoRFID);


            //Aqui eu nao sei se tem que colocar o "id" pra inserir valor nele ja que ele é auto incremento
            String sql = "INSERT INTO dados(data_hora, numCard) VALUES(datetime('now', 'localtime'), '"+cartaoRFID+"')";
            db.exec(sql);


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
  //return content;
  }
void loop(){

content="";

  while (!Serial);     
    SPI.begin();         
    mfrc522.PCD_Init();  
    //Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));
  
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  
//  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle. And if present, select one.
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  } 
  content.toUpperCase();
  Serial.println(content);
if (content != ""){
  testeFunc(content);
  }
}  
