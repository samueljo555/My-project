#include <Adafruit_Fingerprint.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// setting ssid sama password dari wifi yang ingin di hubungkan
const char* ssid = "RealmeX";
const char* password = "samueljose";
// deklarasi variable-variable yang di butuhkan saat sistem berjalan
int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input = D8;
int relay = D7;
int button = D3;
unsigned long myTime;
String address="http://192.168.1.1";
// komunikasi serial yang digunakan antara sensor fingerprint dengan esp32
SoftwareSerial mySerial(D6, D5);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int cek=0;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup()
{
  Serial.begin(9600);
  EEPROM.begin(512);
  lcd.begin();
  lcd.backlight();
  // button sebagai input dimana saat button ditekan maka relay akan aktif yang membuat selenoid terbuka dan akhir air dapat berjalan
  pinMode(button , INPUT);
  // relay untuk mengaktifkan selenoid valve
  pinMode(relay , OUTPUT);
  // input di sini merupakan pin dari sensor waterlflow dimana nanti input ini akan digunakan untuk menghitung volume air yang keluar
  pinMode(input,INPUT);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getParameters();
  finger.getTemplateCount();
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
  delay(10);
  
}
lcd.print("Hallo");
}


void loop()                     // run over and over again
{
  //cek apakah wifi connect atau tidak
if (WiFi.status() == WL_CONNECTED) {
  //deklarasi penggunaan http
  HTTPClient http;
  http.useHTTP10(true);
  // url yang akan di akses oleh esp32, url ini berfungsi untuk mengecek apakah ada user yang mau mendaftar sidik jari atau tidak
  http.begin(address + "/dispenser/data.json");
  //melakukan request get ke url yang sudah di s
  int httpCode = http.GET();
  if (httpCode > 0) {
    //data yang sudah di dapat dari data.json ,akan di olah disini
    StaticJsonDocument<128> doc;
    deserializeJson(doc, http.getStream());
    String dispenser = doc[0]["dispenser"];
    String daftar = doc[0]["daftar"];
    String nama = doc[0]["name"];
    // jika didalam data.json terdapat angkat 1 dan nama tidak kosong , itu tandanya ada yang ingin mendaftarkan sidik jari ke sistem
    if (daftar == "1" && nama != "" && dispenser=="DIS1"){ // jika ada yang ,mendaftar maka if ini akan di eksekusi
      //disini sistem membaca eeprom pada address ke 5, dimana data untuk id fingerprint terakhir disimpan, lalu data tersebut ditambah 1,
      //agar id fingerprint tidak tabrakan
      id = EEPROM.read(5)+1;
      while (!  getFingerprintEnroll() ); // melakukan perulangan untuk membaca fingerprint, jika fingerprint berhasil di baca, maka perulangan
      // akan berhenti
        if (id != 0) {// ID #0 not allowed, try again!
          // jika pendaftaran berhasil , maka id dari fingerprint tersebut akan di simpan kembali , supaya bisa digunakan jika ada orang lain
          // yang ingin mendaftar
        EEPROM.write(5,id);
        EEPROM.commit();
        //ini untuk menyimpan data pendaftar ke database yang ada di server
        http.begin(address + "/dispenser/daftar_ke_database.php?ID=" + String(id) + "&nama=" + nama + "&dispenser=" + dispenser);
        http.GET();
        delay(1000);
        // menghapus data.json ke bentuk tidak ada yang mendaftar , agar tidak di baca kembali oleh sistem.
        http.begin(address + "/dispenser/index.php?dispenser=\"\"&daftar=0&name=\"\"");
        http.GET();
        Serial.print("Succes mendaftarkan fingerprint");
        
      }
    }
    else {//else disini akan di eksekusi jika sistem tidak membaca ada nya orang yang ingin mendaftar sidik jari baru
    cek = getFingerprintIDez(); // untuk membaca sidik jari , jika terdaftar maka orang tersebut di izinkan untuk mengambil air
                                // return dari getFingerprintIDez(); adalah -1 jika gagal dan selain -1 jika berhasil
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Stand By");
    
        
        if(cek!=-1){//jika cek tidak sama dengan -1 maka if ini akan di eksekusi
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Sidik jari");
            lcd.setCursor(0,1);
            lcd.print("Terdaftar");
            delay(1000);
           myTime = millis();
           while(millis()-myTime<3000){ // while disini berfungsi untuk menunggu orang menekan tombol selama 3 detik, jika selama 3 detik tombol
            //tidak di tekan , maka orang tersebut harus kembali menscan sidik jari nya untuk mengambil air
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Tekan Tombol");           
             while(digitalRead(button) == LOW) // while disini berfungsi untuk melakukan perulangan jika tombol ditekan, dimana pada saat perulangan 
             //tersebut sensor water flow akan membaca volume yang keluar selama button di tekan.
             {
                digitalWrite(relay,HIGH);
                X = pulseIn(input, HIGH);
                Y = pulseIn(input, LOW);
                TIME = X + Y;
                FREQUENCY = 1000000/TIME;
                WATER = FREQUENCY/7.5;
                LS = WATER/60;
                if(FREQUENCY >= 0)
                  {
                    if(isinf(FREQUENCY))
                      {
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("VOL. :0.00");
                        lcd.setCursor(0,1);
                        lcd.print("TOTAL:");
                        lcd.print( TOTAL);
                        lcd.print(" L");
                      }
                    else
                      {
                        TOTAL = TOTAL + LS;
                        Serial.println(FREQUENCY);
                        lcd.clear();
                        lcd.setCursor(0,0);
                        lcd.print("VOL.: ");
                        lcd.print(WATER);
                        lcd.print(" L/M");
                        lcd.setCursor(0,1);
                        lcd.print("TOTAL:");
                        lcd.print( TOTAL);
                        lcd.print(" L");
                      }
                }
                
                delay(1000);
              
             }
             
             digitalWrite(relay,LOW);
             delay(10);
           }
           // saat tombol di lepas , maka data dari sensor waterflow yaitu volume dari air yang keluar akan di kirim ke server untuk
           // di simpan ke database.
           http.begin(address + "/dispenser/database.php?Liter=" + String(TOTAL,2) +"&ID=" + String(cek) + "&DIS=" + "DIS1");
           http.GET();
           TOTAL=0;
        }
    }    
  }
  

}
  
  

}

//funsi dari library fingerprint untuk mendaftarkan sidik jari baru
uint8_t getFingerprintEnroll() {

  int p = -1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tempelkan Jari #");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      break;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Place same ");
  lcd.setCursor(0,1);
  lcd.print("finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      break;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
    default:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
      return p;
  }

  // OK converted!

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
    return p;
  } else {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
    return p;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Stored");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
    return p;
  } else {
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Error");
    return p;
  }

  return true;
}
//funsi dari library fingerprint untuk mendapatkan id dari sidik jari yang sudah terdaftar
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  return finger.fingerID;
}
