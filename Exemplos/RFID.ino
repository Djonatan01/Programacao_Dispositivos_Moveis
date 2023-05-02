#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SPI.h>

//Bliblioteca que adiciona o SQLite (Lembrando que tem que pesquisar ela no SKETCH)
#include <SQLite3.h>

#define SS_PIN 21
#define RST_PIN 22

String content= "";


SQLite3 db;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(115200);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  //Serial.println();

  
    //Puxa o diretório onde o BD ta salvo pra abrir ele
    db.open("/home/djonatan/Documentos/GitHub/Programacao_Dispositivos_Moveis/Projeto/RFID/dbRFID.db");
    //Cria a tabela para armazenar as informações do cartão RFID
    db.exec("CREATE TABLE IF NOT EXISTS dados(id INTEGER PRIMARY KEY AUTOINCREMENT, data_hora TEXT, numCard TEXT)");
    
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  Serial.println(content);
  
    //Aqui eu nao sei se tem que colocar o "id" pra inserir valor nele ja que ele é auto incremento
  String sql = "INSERT INTO dados(data_hora, numCard) VALUES(datetime('now', 'localtime'), '"+content+"')";
  db.exec(sql);
  
  delay(1000);
} 
