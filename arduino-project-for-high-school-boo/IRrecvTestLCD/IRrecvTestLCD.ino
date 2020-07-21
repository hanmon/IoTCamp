/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>
#include "codes.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int RECV_PIN = 22, buzzerPin = 4;

IRrecv irrecv(RECV_PIN);

decode_results results;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup()
{
  Serial.begin(115200);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  //Setting buzzerPin
  pinMode(buzzerPin, OUTPUT);
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IR Receive Test");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    printCode(results.value);
    beep();
  }
  delay(100);
}

void beep() {
  //發出2KHz，持續0.25秒的beep聲
    for(int i=0;i<250;i++){
      digitalWrite(buzzerPin,HIGH);
      delayMicroseconds(250);
      digitalWrite(buzzerPin,LOW);
      delayMicroseconds(250);
    }
}

void printCode(unsigned long value) {
  if (value == 0xFF629D) {
    Serial.println("KEY_UP");
    lcd.setCursor(0, 1);
    lcd.print("KEY_UP           ");
  }
  else if (value == 0xFFA857) {
    Serial.println("KEY_DOWN");
    lcd.setCursor(0, 1);
    lcd.print("KEY_DOWN         ");
  }
  else if (value == 0xFF22DD) {
    Serial.println("KEY_LEFT");
    lcd.setCursor(0, 1);
    lcd.print("KEY_LEFT         ");
  }
  else if (value == 0xFFC23D) {
    Serial.println("KEY_DOWN");
    lcd.setCursor(0, 1);
    lcd.print("KEY_DOWN         ");
  }
  else if (value == 0xFF02FD) {
    Serial.println("KEY_OK");
    lcd.setCursor(0, 1);
    lcd.print("KEY_OK          ");
  }
  else if (value == 0xFF6897) {
    Serial.println("KEY_ONE");
    lcd.setCursor(0, 1);
    lcd.print("KEY_ONE         ");
  }
  else if (value == 0xFF9867) {
    Serial.println("KEY_TWO");
    lcd.setCursor(0, 1);
    lcd.print("KEY_TWO         ");
  }
  else if (value == 0xFFB04F) {
    Serial.println("KEY_THREE");
    lcd.setCursor(0, 1);
    lcd.print("KEY_THREE       ");
  }
  else if (value == 0xFF30CF) {
    Serial.println("KEY_FOUR");
    lcd.setCursor(0, 1);
    lcd.print("KEY_FOUR        ");
  }
  else if (value == 0xFF18E7) {
    Serial.println("KEY_FIVE");
    lcd.setCursor(0, 1);
    lcd.print("KEY_FIVE        ");
  }
  else if (value == 0xFF7A85) {
    Serial.println("KEY_SIX");
    lcd.setCursor(0, 1);
    lcd.print("KEY_SIX         ");
  }
  else if (value == 0xFF10EF) {
    Serial.println("KEY_SEVEN");
    lcd.setCursor(0, 1);
    lcd.print("KEY_SEVEN       ");
  }
  else if (value == 0xFF38C7) {
    Serial.println("KEY_EIGHT");
    lcd.setCursor(0, 1);
    lcd.print("KEY_EIGHT       ");
  }
  else if (value == 0xFF5AA5) {
    Serial.println("KEY_NINE");
    lcd.setCursor(0, 1);
    lcd.print("KEY_NINE        ");
  }
  else if (value == 0xFF42BD) {
    Serial.println("KEY_STAR");
    lcd.setCursor(0, 1);
    lcd.print("KEY_STAR       ");
  }
  else if (value == 0xFF4AB5) {
    Serial.println("KEY_ZERO");
    lcd.setCursor(0, 1);
    lcd.print("KEY_ZERO       ");
  }
  else if (value == 0xFF52AD) {
    Serial.println("KEY_SHARP");
    lcd.setCursor(0, 1);
    lcd.print("KEY_SHARP       ");
  }
  else if (value == 0xFFFFFFFF) {
    Serial.println("NEC_REPEAT_CODE");
    lcd.setCursor(0, 1);
    lcd.print("NEC_REPEAT_CODE  ");
  }
  else {
    Serial.println("KEY_UNKNOWN");
    lcd.setCursor(0, 1);
    lcd.print("KEY_UNKNOWN      ");
  }

}
