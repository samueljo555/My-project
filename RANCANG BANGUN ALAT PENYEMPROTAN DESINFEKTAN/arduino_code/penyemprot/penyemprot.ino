#define echoPin 11 //Echo Pin
#define trigPin 12 //Trigger Pin

int relay=7;
bool cek = true;
unsigned long timer;
long duration, distance;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  Serial.println(distance);
  Serial.println(cek);
  if(distance<30 && cek){
    timer = millis();
    while(millis()-timer<5000){
      Serial.println("Masuk");
      digitalWrite(relay,LOW);
    }
    digitalWrite(relay,HIGH);
    cek=false;
  }
  else{
    if(distance>30)
    cek=true;
    delay(1000);
  }
  
}
