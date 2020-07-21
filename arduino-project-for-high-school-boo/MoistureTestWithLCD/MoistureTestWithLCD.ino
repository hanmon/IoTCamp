#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.begin();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Value:");
}
void loop() {
  int sensorValue = analogRead(A0); // read A0 data and assign to sensorValue
  if(sensorValue<10)
  {
  lcd.setCursor(6,0);
  lcd.print(sensorValue);
  lcd.setCursor(7,0);
  lcd.print("    ");
  }
  if(sensorValue<100)
  {
  lcd.setCursor(6,0);
  lcd.print(sensorValue);
  lcd.setCursor(8,0);
  lcd.print("    ");
  }
  if(sensorValue>99)
  {
  lcd.setCursor(6,0);
  lcd.print(sensorValue);
  }
   if(sensorValue<301)
  {
  lcd.setCursor(0,1);
  lcd.print("dry soil       ");
  }
  if((sensorValue>300)&&(sensorValue<501))
  {
  lcd.setCursor(0,1);
  lcd.print("humid soil   ");
  }
     if(sensorValue>500)
  {
  lcd.setCursor(0,1);
  lcd.print("in water       ");
  }
  delay(200);
}
