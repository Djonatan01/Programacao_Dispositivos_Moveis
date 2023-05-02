#include <HTTPClient.h>

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SPI.h>
#include <WiFi.h>

//Incluindo o sistema de senhas do sistema RFID
#include "arduino_secrets.h"


//Definição dos pinos do RFID
#define SS_PIN 21
#define RST_PIN 22

String content= "";

String url = "https://systemrfid.djonatan01.repl.co/rfid_read/";

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SECRET_SSID);

    WiFi.begin(SECRET_SSID, SECRET_password);

    while (WiFi.status() != WL_CONNECTED) {
        HTTPClient http;
        http.begin(url);
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();
}

void loop() {
content= "";
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  //Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println( "Message : " + content);
  
  //enviarPagina(content);
  enviarPagina(content);
  delay(200);
}

void enviarPagina(String cartaoRFID) {
  HTTPClient http;
  
  // Abre uma conexão HTTP para a URL desejada
  http.begin(url + cartaoRFID);
  
  // Define o tipo de conteúdo da requisição como JSON
  http.addHeader("Content-Type", "application/json");
  
  // Monta um objeto JSON com os dados a serem enviados
  String json = "{\"cartaoRFID\": \"" + cartaoRFID + "\"}";
  
  // Envia a requisição POST com os dados JSON
  int httpResponseCode = http.POST(json);
  
  // Verifica o código de resposta da requisição
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  // Fecha a conexão HTTP
  http.end();
}
