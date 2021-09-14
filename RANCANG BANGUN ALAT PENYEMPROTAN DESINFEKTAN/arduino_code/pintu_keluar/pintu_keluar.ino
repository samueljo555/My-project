#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define echoPin 11 //Echo Pin
#define trigPin 12 //Trigger Pin
long duration, distance;
const char* ssid = "COVID-19";
const char* password = "pakaimasker";
bool cek = true;
bool cekcek=true;
unsigned long timerr;
void setup() {
  Serial.begin(115200);

  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {

 Serial.print("Connecting... ");
  delay(1000);
}
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  Serial.println("jose");
  if (WiFi.status() == WL_CONNECTED) {
    
    HTTPClient http;
    http.useHTTP10(true);
    digitalWrite(trigPin, LOW);delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration/58.2;

    if(distance<=10 && distance>=1 && cekcek){
        if(cek){
          timerr = millis();
          cek = false;
        }
        if(cek && (millis()-timerr>2000)){
          http.begin("http://192.168.43.238/adminlte/updatejson.php?data=A,,,1");
          cek = true;
          cekcek = false;
        }
    }
    else{
      cekcek = true;
    }
     http.end();
  }
delay(3000);
}
