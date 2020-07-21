
#include <LiquidCrystal_I2C.h>
int pirPin = 2, greenLedPin = 9, redLedPin = 8 ;
bool pirState = LOW;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("PIR Test Program");
  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(pirPin,INPUT);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("PIR State:");
}

void loop() {
    pirState = digitalRead(pirPin);
//    digitalWrite(ledPin, pirState);
    if (pirState) {
      Serial.println("Motion Detected!");
      lcd.setCursor(0, 1);
      lcd.print("Motion Detected");
      //Turn on red Led and turn off green led
      digitalWrite(greenLedPin,HIGH);
      digitalWrite(redLedPin,LOW);
    }
    else {
      Serial.println("Motion Ended!");
      lcd.setCursor(0, 1);
      lcd.print("Motion Ended    ");
      //Turn on green Led and turn off red led
      digitalWrite(greenLedPin,LOW);
      digitalWrite(redLedPin,HIGH);
      
    }


  // put your main code here, to run repeatedly:

}
