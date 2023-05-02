#include <HTTPClient.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SPI.h>
#include <WiFi.h>
#include "arduino_secrets.h"

// Definição dos pinos do RFID
const int SS_PIN = 21;
const int RST_PIN = 22;

MFRC522 mfrc522(SS_PIN, RST_PIN);

// DECLARAÇÃO DE FUNÇÕES
void connectWiFi();
void readRFID();
void sendRFID(String rfid);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Aproxime o cartão do leitor...");

  // Chamar a conexão com WiFi
  connectWiFi();
}

void loop() {
  readRFID();
  delay(200);
}

void readRFID() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String rfid;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  rfid.toUpperCase();
  Serial.println("Cartão lido: " + rfid);
  sendRFID(rfid);
}

void sendRFID(String rfid) {
  HTTPClient http;
  String url = "http://127.0.0.1:5000/rfid";
  String payload = "rfid=" + rfid;
  Serial.println("Enviando cartão RFID: " + payload);
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode == 200) {
    Serial.println("Cartão RFID enviado com sucesso");
  } else {
    Serial.println("Erro ao enviar o cartão RFID: " + String(httpResponseCode));
  }
  http.end();
}

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
