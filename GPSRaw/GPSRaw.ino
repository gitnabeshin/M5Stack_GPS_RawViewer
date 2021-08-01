/******************************************
 * NEO-6M GPS Module with M5Stack
 * 
 ******************************************/
#include <M5Stack.h>
#include <SoftwareSerial.h>

SoftwareSerial GroveA(21, 22);
String recv_str;
bool isFirst = true;

void setup() {
  M5.begin();
  GroveA.begin(9600);

  Serial.println("hello");
  M5.Lcd.setTextFont(4);
  M5.Lcd.setCursor(40, 0, 4);
  M5.Lcd.setTextColor(BLUE);
  M5.Lcd.println(("GPS Raw Data Viewer"));
  M5.Lcd.setCursor(0, 30, 2);
  M5.Lcd.setTextColor(WHITE);
} 

void loop() {
  M5.update();

  if(GroveA.available()) {
    if(isFirst){
      M5.Lcd.clear();
      M5.Lcd.setCursor(40, 0, 4);
      M5.Lcd.setTextColor(BLUE);
      M5.Lcd.println(("GPS Raw Data Viewer"));
      M5.Lcd.setCursor(0, 30, 2);
      M5.Lcd.setTextColor(WHITE);
      isFirst = false;
    }

    recv_str = GroveA.readStringUntil('\n');
    Serial.println(recv_str);
    M5.Lcd.println(recv_str);

    // last line of unit
    if(recv_str.startsWith("$GPGLL")){
      Serial.println();
      M5.Lcd.println();
      isFirst = true;      
    }
  }
  delay(10);
}
