/* Electronic Clock (Arduino電子鐘)
   Functionality:
   An electronic clock which is capable of keep running even after power off.
   Reset the current time to default by letting pin7 as HIGH.
   Components:
   1.DS1302 RST, DATA, CLK attached to Arduino Uno/MEGA2560 pin 2,3,4
   2.I2C LCD SCL, SDA attached to Arduino Uno/MEGA2560 pin 21,20
   3.Slide switch attached to Arduino Uno/MEGA2560 pin3
   Using Library:
   1.I2C Liquid Crystal library (https://github.com/johnrickman/LiquidCrystal_I2C)
   2.DS1302 library  (http://jmaker.banner.tw/blog/DS1302.zip)
   3.Time library (https://www.arduinolibraries.info/libraries/time)

   Create Date:2019-07-27
   Author: Bruce Chiu
   Modified Date:2019-08-22
   Author: Bruce Chiu
   Email: boo.chiu@gmail.com
*/
//#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
DS1302 rtc(17, 16, 15); //初始化RTC，使用17,16,15三個pin控制RTC模組的RST、DATA、CLK
//DS1302 rtc(25, 27, 29); //初始化RTC，使用23,25,27三個pin控制RTC模組的RST、DATA、CLK
LiquidCrystal_I2C lcd(0x27, 16, 2);
char* monthName[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char* weekDayName[] = {"Sun.", "Mon.", "Tue.", "Wed.", "Thr.", "Fri.", "Sat."};
const int slideSwitchPin = 14;
void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  //init I2C LCD Monitor
  lcd.begin();
  lcd.backlight();

  //Pin7設定為內部上拉，若Pin7狀態為HIGH，則重設時鐘時間
  pinMode(slideSwitchPin, INPUT_PULLUP);
  if (digitalRead(slideSwitchPin) == HIGH) {
    rtc.setTime(11, 30, 0);     // Set the time to 12:00:00 (24hr format)
    rtc.setDate(25, 7, 2020);   // Set the date to August 6th, 2010
  }

  Time t = rtc.getTime();
  Serial.begin(115200);
  setTime(t.hour, t.min, t.sec, t.date, t.mon, t.year); //setTime(hr,min,sec,day,month,yr); set time to noon June 23 2019
}

void loop()
{
  digitalClockDisplay();
  //delay(1000);
}

void digitalClockDisplay() {
  // digital clock display of the time
  lcd.setCursor(0, 0);
  printDigits(hour());
  lcd.print(":");
  printDigits(minute());
  lcd.print(":");
  printDigits(second());
  lcd.setCursor(9, 0);
  lcd.print(weekDayName[weekday()-1]);
  lcd.setCursor(0, 1);
  //  Serial.print(" ");
  printDigits(day());
  lcd.print(" ");
  lcd.print(monthName[month() - 1]);
  lcd.print(" ");
  lcd.print(year());
}

void printDigits(int digits) {
  // utility function for clock display: prints preceding colon and leading 0

  if (digits < 10)
    //Serial.print('0');
    lcd.print('0');
  //Serial.print(digits);
  lcd.print(digits);
}
