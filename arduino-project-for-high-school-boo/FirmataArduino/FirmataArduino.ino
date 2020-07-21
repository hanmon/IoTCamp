

/*
   Firmata is a generic protocol for communicating with microcontrollers
   from software on a host computer. It is intended to work with
   any host computer software package.

   To download a host software package, please click on the following link
   to open the list of Firmata client libraries in your default browser.

   https://github.com/firmata/arduino#firmata-client-libraries
*/

/* Supports as many analog inputs and analog PWM outputs as possible.

   This example code is in the public domain.
*/
#include <Firmata.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte previousPIN[TOTAL_PORTS];  // PIN means PORT for input
byte previousPORT[TOTAL_PORTS];
byte analogPin = 0;
char note;
int freqMap[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 523}; //音符的代號頻率
char noteChar[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B', '1', '2', '3', '4', '5', '6', '7', 'c'};
//int freqMap[] = {262, 294, 330, 349, 392, 440, 494}; //音符的代號頻率
//char noteChar[] = {'1', '2', '3', '4', '5', '6', '7'};
const int buzzerPin = 7;

void analogWriteCallback(byte pin, int value)
{
  if (IS_PIN_PWM(pin)) {
    //pinMode(PIN_TO_DIGITAL(pin), OUTPUT);
    analogWrite(PIN_TO_PWM(pin), value);
  }
}

void setPinModeCallback(byte pin, int mode) {
  if (IS_PIN_DIGITAL(pin)) {
    pinMode(PIN_TO_DIGITAL(pin), mode);
    lcd.setCursor(0, 0);
    lcd.print("Got pin" + String(pin));
    lcd.setCursor(0, 1);
    lcd.print("mode " + String(mode));
  }
}

void digitalWriteCallback(byte port, int value)
{
  byte i;
  byte currentPinValue, previousPinValue;

  if (port < TOTAL_PORTS && value != previousPORT[port]) {
    for (i = 0; i < 8; i++) {
      currentPinValue = (byte) value & (1 << i);
      previousPinValue = previousPORT[port] & (1 << i);
      if (currentPinValue != previousPinValue) {
        digitalWrite(i + (port * 8), currentPinValue);
      }
    }
    previousPORT[port] = value;
    lcd.setCursor(0, 0);
    lcd.print("Got port " + String(port));
    lcd.setCursor(0, 1);
    lcd.print("value: " + String(value));
  }
}

void stringCallback(char *myString) {
  lcd.setCursor(0, 0);
  lcd.print(myString);
}

void outputPort(byte portNumber, byte portValue)
{
  // only send the data when it changes, otherwise you get too many messages!
  if (previousPIN[portNumber] != portValue) {
    Firmata.sendDigitalPort(portNumber, portValue);
    previousPIN[portNumber] = portValue;
  }
}


void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
  Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.attach(STRING_DATA, stringCallback);
  //Firmata.attach(SET_PIN_MODE, setPinModeCallback);
  Firmata.begin(57600);
  lcd.begin();
  lcd.backlight();
  lcd.print("Hello, world!");
}

void loop()
{
  static unsigned long lastestTime = 0;
  //  while (Firmata.available()) {
  //    Firmata.processInput();
  //  }
  // do one analogRead per loop
  //  if (millis() - lastestTime > 1000) {
  //    Firmata.sendAnalog(analogPin, analogRead(analogPin));
  //    lastestTime = millis();
  //  }
  if (Serial.available() > 0) {
    note = Serial.read();
    //noTone(buzzerPin);
    tone(buzzerPin, freqMap[note], 1000 / 4);
  }


}

void serialEvent() {

}
