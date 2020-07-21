#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int ledPin=9,lightSensorDOPin=6;                 //Connect the LED  to Pin13 Digital 13
const int thresholdvalue=30;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K
// LCM1602 I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address

void setup() {
  Serial.begin(9600);                //Start the Serial connection
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 13 as an OUTPUT
  pinMode(lightSensorDOPin,INPUT);
  lcd.begin();               // initialize the lcd 
  lcd.backlight();

}
void loop() {
  int sensorValue = analogRead(A0); 
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
  if(Rsensor<thresholdvalue)
  {
    digitalWrite(ledPin,LOW); //for Common Anode RGB
  }
  else
  {
  digitalWrite(ledPin,HIGH);
  }
  Serial.println("the analog read data is ");
  Serial.println(sensorValue);
  Serial.println("the sensor resistance is ");
  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
  
  lcd.clear();
  lcd.setCursor ( 0, 0 );        // go to home
  lcd.print("Light:"); 
  lcd.print(1023-sensorValue);
  lcd.setCursor ( 0, 1 );
  lcd.print("DO State:");
  lcd.print(digitalRead(lightSensorDOPin)?"HIGH":"LOW");
  delay(1000);
}
