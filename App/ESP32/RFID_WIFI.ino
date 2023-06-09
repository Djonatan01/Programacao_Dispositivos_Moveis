#include <HTTPClient.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SPI.h>
#include <WiFi.h>
// Projeto 13 - Servo motor controlado por Arduino
#include <ESP32Servo.h>

//Incluindo o sistema de senhas do sistema RFID
#include "arduino_secrets.h"

//Definição dos pinos do RFID
#define SS_PIN 21
#define RST_PIN 22
#define greenLed 4
#define redLed 2

// Cria um objeto servo
Servo servo1; 

String content= "";

String url = "https://app.easyinout.repl.co/traffic/register/";

// Agrega o objeto servo1 ao pino digital 11
static const int servoPin = 12;
// Variável para armazenar a posição do servo1
int pos = 0;

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
    
    server.begin();

    // Set servo PWM frequency to 50Hz
  servo1.attach(servoPin);  
  // Attach to servo and define minimum and maximum positions
  // Modify as required

   pinMode(redLed, OUTPUT);
   pinMode(greenLed, OUTPUT);
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
    String response;
  // Verifica o código de resposta da requisição
  if (httpResponseCode == 200) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    response = http.getString();
    Serial.println(response);   
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  servoRet(response);
  // Fecha a conexão HTTP
  http.end();
}

void servoRet(String resposta){
 if (resposta == "1") {               
        servo1.write(90);
        digitalWrite(greenLed, HIGH);         
        delay(2500);
        digitalWrite(greenLed, LOW);
        servo1.write(1);
      }else{
        servo1.write(1);
        digitalWrite(redLed, HIGH);
        delay(2500);
        digitalWrite(redLed, LOW);
       }
}