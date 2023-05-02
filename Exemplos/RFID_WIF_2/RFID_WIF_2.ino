#include <WiFi.h>
#include <HTTPClient.h>

#include  "arduino_secrets.h"

//Your Domain name with URL path or IP address with path
//String serverName = "http://127.0.0.1:5000/";

void setup() {
 
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
void loop() {
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   //http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
   http.begin("http://127.0.0.1:5000/");
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
  
   int httpResponseCode = http.POST("POSTING from ESP32");   //Send the actual POST request
  
   if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(10000);  //Send a request every 10 seconds
  
}