#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int ledPin=13,moistureDoPin=3;                 //Connect the LED  to Pin13 Digital 13
const int thresholdvalue=35;         //The threshold for which the LED or Relay should turn on. 
float Rsensor; //Resistance of sensor in K
// LCM1602 I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address

void setup() {
  Serial.begin(9600);                //Start the Serial connection
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 13 as an OUTPUT
  pinMode(moistureDoPin,INPUT);            //Set the LED on Digital 13 as an OUTPUT
  lcd.begin();               // initialize the lcd 
  lcd.backlight();
}

void loop() {
  int sensorValue = analogRead(A0);
  int Humi =  map(sensorValue, 0, 385, 0, 1000);

  Rsensor= (Humi/10.0);
  
  if(Rsensor<thresholdvalue)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
  digitalWrite(ledPin,LOW);
  }
  Serial.print("The analog read data is :");
  Serial.println(sensorValue);
  Serial.print("The Mositure Huminity  is : ");
  Serial.print(Rsensor);//show the  Mositure Huminity  on the serial monitor;
  Serial.println(" %");

  //lcd.clear();
  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Mositure:"); 
  lcd.print(sensorValue);
  lcd.print("         ");
  lcd.setCursor ( 0, 1 );        // go to home
  lcd.print(digitalRead(moistureDoPin)?"Help!I'm thirsty":"I'm okay.         "); 
  delay(1000);
}
