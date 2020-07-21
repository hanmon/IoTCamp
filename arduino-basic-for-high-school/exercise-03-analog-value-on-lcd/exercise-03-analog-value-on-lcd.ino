//由LCD顯示串列輸入的內容，Pin3與Pin4以正向邏輯方式連接
#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Addr, En, Rw, Rs, d4, d5, d6, d7, backlighpin, polarity
const int rightPin = 3, leftPin = 4;
void setup()
{
  lcd.begin(16, 1);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Anaglog Value");
  lcd.setCursor(0, 1);
  lcd.print("On LCD");
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  Serial.begin(115200);
}
void loop()
{
  static int lastestValue = 0;
  //read A0 value
  int currentValue = analogRead(A0);

  if (currentValue != lastestValue)
  {
    delay(100);// wait a bit for the entire message to arrive
    lcd.clear();// clear the screen
    lcd.print("AO:"+String(currentValue));// display each character to the LCD
    lastestValue=currentValue;
  }
  if (digitalRead(rightPin) == HIGH && digitalRead(leftPin) == LOW) {
    lcd.scrollDisplayRight();
    delay(150);
  }
  else if (digitalRead(rightPin) == LOW && digitalRead(leftPin) == HIGH) {
    lcd.scrollDisplayLeft();
    delay(150);
  }
}
