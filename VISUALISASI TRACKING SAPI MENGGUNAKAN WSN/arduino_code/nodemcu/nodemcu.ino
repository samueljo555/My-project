#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <LoRa.h>
#include<String.h>
#include<SPI.h>
const char* ssid = "RealmeX";
const char* password = "samueljose";
String address="http://192.168.43.238";
#define ss 15
#define rst 16
#define dio0 2



void setup() 
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(10);
  
}
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) 
  {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
  Serial.println("LoRa Started");
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.useHTTP10(true);
    String str1="";
    int packetSize = LoRa.parsePacket();
    if (packetSize) 
      {
        Serial.print("Received packet ");
        while (LoRa.available()) 
          {
              str1=str1+((char)LoRa.read()); 
          }
        http.begin(address + "/SAPITRACKER/updateJson.php?data=" + str1);
        Serial.println(address + "/SAPITRACKER/updateJson.php?data=" + str1);
        int httpCode = http.GET();
        Serial.println(httpCode);
        delay(500);
      }
  }
}
