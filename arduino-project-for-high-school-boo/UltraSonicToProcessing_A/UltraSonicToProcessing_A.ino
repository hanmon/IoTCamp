//LCD Library version:1.1 Compatible with the Arduino IDE 1.0
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int TrigPin = 11;
const int EchoPin = 12;
float distance = 0;
const int buzzerPin = 4;
unsigned long lastBeepTime = 0, lastDisplayTime = 0;
unsigned int beepInterval = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(115200);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  lcd.begin();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parking Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Detecting...");
  delay(2000);

}
void loop()
{
  delay(10);
  //發一個10ms的高脈衝去觸發TrigPin
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  distance = pulseIn(EchoPin, HIGH) / 58.0; //算成釐米
  distance = (int(distance * 100.0)) / 100.0; //保留兩位小數
  distance = distance - 0.62; // 　扣掉距離誤差值　
  //透過Serial port傳送至Host PC
  delay(10);
  if (distance < 0) {
    distance = 0;
  }
  Serial.print('H');
  Serial.println(distance);
  // LCD Display
  if (millis() - lastDisplayTime > 1000) {
    lcd.clear();
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print("Distance:");
    lcd.setCursor(0, 1); // 設定游標位置在第一行行首
    lcd.print(distance);
    lcd.print("cm");
    lastDisplayTime = millis();
  }
  beepInterval = map(distance, 0, 450, 100, 4500);
  if (millis() - lastBeepTime > beepInterval) {
    tone(buzzerPin, 2000, 100);
    lastBeepTime = millis();
    Serial.println(beepInterval);
  }




}
