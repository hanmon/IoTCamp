#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "flash.h"
#include "marioStar.h"
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  // put your main code here, to run repeatedly:
  display.drawBitmap(0,0,flash,128,64,1);
  display.display();
  delay(10000);
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.print("Number1:");
  display.println(random(0,100));
  display.print("Number2:");
  display.println(random(0,100));
  display.print("Number3:");
  display.println(random(0,100));
  display.display();
  delay(2000);

  
}
