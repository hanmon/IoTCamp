/*
 * Example of simple security system using PIR Sensor
 * Components: I2C LCD Monitor attached to pin 20 and 21 on MEGA2560, Reed relay attached to pin2
 * Door state HIGH when megnetic apparts from reed relay
 * Author:Bruce Chiu
 * Date:2019/07/22
 * Email:boo.chiu@gmail.com
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "marioStar.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//Including I2C LCD Library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
//const int reedRelayPin = 19;
const int pirPin = 2;//紅外線
const int setArmPin=3;//指撥開關
const int ledPin = 13;//改成13
const int buzzerPin=4;
//const int debounceTime = 200;
volatile boolean detectState = LOW;
boolean armState=LOW;
volatile unsigned long lastTriggeredTime = 0;
//counting interrupts
volatile int intCount=0;
char msgDetected[]="Detected";
char msgNone[]="None";



void setup() {
  //如果使用磁簧開關，請將INPUT_PULLUP當作pinMode的第二個參數
  pinMode(pirPin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(reedRelayPin), btnHandlerArduino, CHANGE);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  initLCD();
  initOLED();
  pinMode(setArmPin,INPUT_PULLUP);
  display.println("Simple Security System");
  lcd.setCursor(0,0);
  lcd.print("Simple Security System");
}

void loop() {
  // put your main code here, to run repeatedly:
  //if door state==HIGH, the door/window is open
  display.clearDisplay();
  display.setCursor(0,0);
  armState=digitalRead(setArmPin);
  detectState=digitalRead(pirPin);
  //Show security state
  if(armState){
    //display.setCursor(0,2);
    display.println("Armed");
    lcdPrint("Armed                 ",0);
  }
  else
  {
    //display.setCursor(0,4);
    display.println("DisArmed");
    lcdPrint("DisArmed              ",0);
  }
  //Show door state
  if(detectState){
    display.println(msgDetected);
    lcdPrint(msgDetected,1);
  }
  else{
    display.println(msgNone);
    lcdPrint(msgNone,1);
  }
  //Make sound when armed and door opened
  if(armState && detectState){
    tone(buzzerPin,1000);
    delay(500);
    noTone(buzzerPin);
  }
  else{
    noTone(buzzerPin);
  }
  display.display();
  
}

void initOLED() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

}

void initLCD() {
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Security System      ");
  lcd.setCursor(0, 1);
  lcd.print("Starts");
  delay(3000);
  lcd.clear();
}

void lcdPrint(char* strPtr, int row) {
  lcd.setCursor(0, row);
  lcd.print(strPtr);
}
