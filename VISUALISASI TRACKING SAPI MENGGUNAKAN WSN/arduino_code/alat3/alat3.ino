#include <DS3231.h>
#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL); 
TinyGPSPlus gps;
SoftwareSerial ss(4, 5);
bool cek = true;
void setup()
{
  // Setup Serial connection
  Serial.begin(9600);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // Initialize the rtc object
  rtc.begin();
  ss.begin(9600);
  // The following lines can be uncommented to set the date and time
}

void loop()
{
   while(ss.available()>0){
  if(gps.encode(ss.read())){
    }
   }
  Serial.println();
  String a = rtc.getTimeStr();
  int timee = a.substring(6,8).toInt();
  Serial.println(timee);
  if((timee <= 15 && timee > 10) || (timee <= 30 && timee > 25) || (timee <= 45 && timee > 40) || (timee <= 59 && timee > 55) || (timee == 0)){ // 

   if (gps.location.isValid()){
    LoRa.beginPacket();
    LoRa.print("data3%20:%20"+String(gps.location.lat(),6) +","+ String(gps.location.lng(), 6));
    Serial.println("data3%20:%20"+String(gps.location.lat(),6) +","+ String(gps.location.lng(), 6));
    LoRa.endPacket(); 
  }
  else{
     LoRa.beginPacket();
    LoRa.print("invalid 3");
    Serial.println("invalid 3");
    LoRa.endPacket();      
  }
  }
//  delay(1000);
}
