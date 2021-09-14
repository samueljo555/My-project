#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <Arduino.h>
#include <SimpleTimer.h>
#define FIREBASE_HOST "garin-3dad7-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "3fQBwYKcXrsmns5dUZamgpxKJ2qrufJa6vUQSwyc"
#define WIFI_SSID "RealmeX"
#define WIFI_PASSWORD "samueljose"
SimpleTimer timer;
String myString; // complete message from arduino, which consists of snesors data
char rdata; // received characters
String data;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

timer.setInterval(1000L,sendata); 
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.run();
while (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
    if(rdata=='\n'){
        
      myString[myString.length()-2]='\0';
      data = myString;
      Serial.flush();
    }
    delay(20);
    }
    myString="";
    
}


void sendata(){
  Serial.println(data);
  Firebase.setString("data",data);
  if (Firebase.failed()) { 
   Serial.print("setting /number failed:"); 
   Serial.println(Firebase.error());   
  }
}
