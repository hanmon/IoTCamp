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
#include "marioStar.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int reedRelayPin = 2;
const int setArmPin=3;
const int ledPin = 13;
const int buzzerPin=4;
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
  display.setTextSize(1);
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
  pinMode(setArmPin,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //if door state==HIGH, the door/window is open
  armState=digitalRead(setArmPin);
  //Show security state
  armState? lcdPrint("Armed   ",0): lcdPrint("DisArmed",0);
  //Show door state
  doorState? lcdPrint("Opened",1): lcdPrint("Closed",1);
  //Make sound when armed and door opened
  if(armState && doorState){
    tone(buzzerPin,1000);
    delay(500);
    noTone(buzzerPin);
  }
  else{
    noTone(buzzerPin);
  }
    
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
