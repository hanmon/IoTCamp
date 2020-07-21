//Including I2C LCD Library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void initLCD() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Security System");
  lcd.setCursor(0, 1);
  lcd.print("Starts");
  delay(3000);
  lcd.clear();
}

void lcdPrint(char* strPtr, int row) {
  lcd.setCursor(0, row);
  lcd.print(strPtr);
}
