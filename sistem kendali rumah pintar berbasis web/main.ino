#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
const uint16_t kIrLed = D2;
int bulb_A = D1;
int bulb_B = D6;
int bulb_RGB = D0;
int tirai_A = D5;
int colok_A = D7;
IRsend irsend(kIrLed);
const char* ssid = "NAINGSIMA";
const char* password = "Sosorbayon";
 
void setup () {
pinMode(bulb_A, OUTPUT);
pinMode(bulb_B, OUTPUT);
pinMode(bulb_RGB, OUTPUT);
pinMode(tirai_A, OUTPUT);
pinMode(colok_A, OUTPUT);
irsend.begin();
Serial.begin(115200);
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}
 
}
 
void loop() {
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
http.useHTTP10(true);
http.begin("http://192.168.100.12/enjoy/data.json");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
if (httpCode > 0) { //Check the returning code
const size_t capacity = JSON_ARRAY_SIZE(5) + 4*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 150;
DynamicJsonDocument doc(capacity);

deserializeJson(doc, http.getStream());
String bulb1 = doc[0]["switch"];
String bulb2 = doc[1]["switch"];
String tirai = doc[2]["switch"];
String colok = doc[3]["switch"];
String bulb3 = doc[4]["switch"];
String rgb = doc[4]["rgb"];
//serializeJson(doc[0]["name"], Serial);
;
if(bulb1=="on1"){
  digitalWrite(bulb_A,LOW);
  }
else{
    digitalWrite(bulb_A,HIGH);
  }
  
if(bulb2=="on2"){
  digitalWrite(bulb_B,LOW);
  }
else{
    digitalWrite(bulb_B,HIGH);
  }
  
if(tirai=="open"){
  digitalWrite(tirai_A,LOW);
  }
else{
    digitalWrite(tirai_A,HIGH);
  }
  
if(colok=="on5"){
  digitalWrite(colok_A,LOW);
  }
else{
    digitalWrite(colok_A,HIGH);
  }

if(bulb3=="on3"){
  digitalWrite(bulb_RGB,LOW);
  irsend.sendNEC(0xFFE01F,32);
  delay(250);
  Serial.println("masuk");
   if(rgb=="red"){
    irsend.sendNEC(0xFF906F,32);
    Serial.println("merah");
    }
    else if(rgb=="green"){
      Serial.println("hijau");
      irsend.sendNEC(0xFF10EF,32);
    }
    else if(rgb=="white"){
      Serial.println("putih");
      irsend.sendNEC(0xFFD02F,32);
    }
    else if(rgb=="blue"){
      Serial.println("biru");
      irsend.sendNEC(0xFF50AF,32);
    }     
    else if(rgb=="yellow"){
      Serial.println("kuning");
      irsend.sendNEC(0xFF8877,32);
    }
    else if(rgb=="orange"){
      Serial.println("orange");
      irsend.sendNEC(0xFFA857,32);
    }    
  }
else{
  irsend.sendNEC(0xFF609F,32);
    digitalWrite(bulb_RGB,HIGH);
  }  
}
 
http.end();   //Close connection
 
}
delay(500);    //Send a request every 1 seconds 
}