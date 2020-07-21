#include <math.h>
const int ledPin=13;                 //Connect the LED  to Pin13 Digital 13
const int thresholdvalue=10;         //The threshold for which the LED should turn on. 
float Rsensor; //Resistance of sensor in K
void setup() {
  Serial.begin(9600);                //Start the Serial connection
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 13 as an OUTPUT
}
void loop() {
  int sensorValue = analogRead(A0); 
  Rsensor=(float)(1023-sensorValue)*10/sensorValue;
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
  Serial.print("The Light sensor resistance is : ");
  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;
  delay(500);
}

