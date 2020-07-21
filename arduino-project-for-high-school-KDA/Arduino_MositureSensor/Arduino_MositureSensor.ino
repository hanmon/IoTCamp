#include <math.h>
const int ledPin=13;                 //Connect the LED  to Pin13 Digital 13
const int thresholdvalue=35;         //The threshold for which the LED or Relay should turn on. 
float Rsensor; //Resistance of sensor in K

void setup() {
  Serial.begin(9600);                //Start the Serial connection
  pinMode(ledPin,OUTPUT);            //Set the LED on Digital 13 as an OUTPUT
}

void loop() {
  int sensorValue = 1023-analogRead(A1);
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
  delay(300);
}

