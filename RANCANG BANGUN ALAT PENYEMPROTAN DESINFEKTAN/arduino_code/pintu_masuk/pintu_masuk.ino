#include <Wire.h>
//#include <Servo.h>
//Servo myservo; 
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define echoPin D4 //Echo Pin
#define trigPin D3 //Trigger Pin
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const byte RATE_SIZE = 10;
float rates[RATE_SIZE];
long duration, distance;
const char* ssid = "RealmeX";
const char* password = "samueljose";
//int Rselenoid = 8;
//int servo = 9;
float suhu=0;
byte rateSpot = 0;
bool cek_body=false;
unsigned long timer =0;
int EN = D5;
int A4 = D6;
int A3 = D7;
void setup() {
  Serial.begin(9600);
  pinMode(EN , OUTPUT);
  pinMode(A4 , OUTPUT);
  pinMode(A3 , OUTPUT);
//  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
//
 Serial.print("Connecting... ");
  delay(1000);
}
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  pinMode(Rselenoid, OUTPUT);
//  pinMode(servo, OUTPUT);
//  Serial.println("Adafruit MLX90614 test");  
  mlx.begin(); 
//  myservo.attach(servo);   
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    
    HTTPClient http;
    http.useHTTP10(true);
    digitalWrite(trigPin, LOW);delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration/58.2;
    +Serial.println(distance);
  
    if(distance>1 &&distance<=7){
      timer = millis();
      Serial.println("object terdeteksi");
      while(millis()-timer<1000){
        float suh = mlx.readObjectTempC();
        Serial.println(suh);
            rates[rateSpot++] = suh;
            rateSpot %= RATE_SIZE; 
            delay(20);
        }
        suhu = 0;
            for (byte x = 0 ; x < RATE_SIZE ; x++){
              suhu += rates[x];
            }
            suhu /= RATE_SIZE;
            suhu = suhu +2;
      cek_body = true;
    }
    else{
      cek_body = false;
    }
    Serial.print("Suhu tubuh  = ");
    Serial.println(suhu);
    if(cek_body && suhu < 32 ){
      http.begin("http://192.168.43.238/adminlte/updatejson.php?data=A,"+ String(suhu,2) +",3,");
      http.GET();
      Serial.println("error");
    }
    else if(cek_body && suhu >=32 && suhu <37.4 ){
      http.begin("http://192.168.43.238/adminlte/updatejson.php?data=A,"+ String(suhu,2) +",1,");
      http.GET();
      Serial.println("aman");
      digitalWrite(EN,HIGH);
      digitalWrite(A3,LOW);
      digitalWrite(A4,HIGH);
      delay(6000);
      digitalWrite(A3,LOW);
      digitalWrite(A4,LOW);

      delay(15000);
      digitalWrite(A3,HIGH);
      digitalWrite(A4,LOW);
      delay(6000);
      digitalWrite(A3,LOW);
      digitalWrite(A4,LOW);
    }
    else if(cek_body &&suhu >37.4 ){
      http.begin("http://192.168.43.238/adminlte/updatejson.php?data=A,"+ String(suhu,2) +",2,");
      http.GET();
      Serial.println("Terdeteksi COVID");
    }
  http.end();
  }

delay(4000);
}
