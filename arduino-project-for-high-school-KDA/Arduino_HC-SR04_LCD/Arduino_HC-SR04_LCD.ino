//LCD Library version:1.1 Compatible with the Arduino IDE 1.0 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int TrigPin = 11; 
const int EchoPin = 12; 
float cm; 
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() 
{ 
Serial.begin(9600); 
pinMode(TrigPin, OUTPUT); 
pinMode(EchoPin, INPUT); 

  lcd.begin();                      // initialize the lcd
 // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DistanceDetector");
  lcd.setCursor(0, 1);
  lcd.print("Provide by KDA");
  delay(2000);

} 
void loop() 
{ 
 delay(100); 
//发一个10ms的高脉冲去触发TrigPin 
digitalWrite(TrigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(TrigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin, LOW); 
cm = pulseIn(EchoPin, HIGH) / 58.0; //算成厘米 
cm = (int(cm * 100.0)) / 100.0; //保留两位小数 
cm = cm -0.62;  // 　扣掉距離誤差值　
Serial.print(cm); 
Serial.print("cm"); 
Serial.println(); 
delay(500); 

// LCD Display
 lcd.clear();
 lcd.setCursor(0, 0); // 設定游標位置在第一行行首
 lcd.print("Distance:");
 lcd.setCursor(0, 1); // 設定游標位置在第一行行首
 lcd.print(cm);
 lcd.print("cm");
}
