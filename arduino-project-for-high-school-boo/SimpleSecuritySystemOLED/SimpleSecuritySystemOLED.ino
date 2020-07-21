/*
 * Example of simple security system using reed relay
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

const int reedRelayPin = 19;
const int setArmPin=18;
const int ledPin = 8;
const int buzzerPin=7;
const int debounceTime = 200;
volatile boolean doorState = LOW;
boolean armState=LOW;
volatile unsigned long lastTriggeredTime = 0;
//counting interrupts
volatile int intCount=0;
char msgOpen[]="Door Open";
char msgClosed[]="Door Closed";

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

void setup() {
  pinMode(reedRelayPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(reedRelayPin), btnHandlerArduino, CHANGE);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  initLCD();
  initOLED();
  pinMode(setArmPin,INPUT_PULLUP);
  display.println("Simple Security System");
}

void loop() {
  // put your main code here, to run repeatedly:
  //if door state==HIGH, the door/window is open
  display.clearDisplay();
  display.setCursor(0,0);
  armState=digitalRead(setArmPin);
  //Show security state
  if(armState){
    //display.setCursor(0,2);
    display.println("Armed");
    lcdPrint("Armed   ",0);
  }
  else
  {
    //display.setCursor(0,4);
    display.println("DisArmed");
    lcdPrint("DisArmed",0);
  }
  //Show door state
  if(doorState){
    display.println("Opened");
    lcdPrint("Opened",1);
  }
  else{
    display.println("Closed");
    lcdPrint("Closed",1);
  }
  //Make sound when armed and door opened
  if(armState && doorState){
    tone(buzzerPin,1000);
    delay(500);
    noTone(buzzerPin);
  }
  else{
    noTone(buzzerPin);
  }
  display.display();
  
}

//Arduino中斷向量
void btnHandlerArduino() {
  if(millis()-lastTriggeredTime>debounceTime){
    doorState=digitalRead(reedRelayPin);
      digitalWrite(ledPin,doorState);
  }
  lastTriggeredTime=millis();
  intCount++;
}
