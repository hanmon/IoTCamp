/*
   4 digits guessing number game
   The circuit:
   1602 I2C LCD Monitor attached to pin20(SDA),pin21(SCL) on MEGA2560
   4x4 button matrix attached to pin 31,33,35,37,39,41,43,45 on MEGA2560

   Created 2019-08-20
   By Bruce Chiu
   Email: boo.chiu@gmail.com
*/

//for arduino uno
//int rowPins[]={11,10,9,8};
//int columnPins[]={7,6,5,4};

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//for arduino MEGA 2560
int rowPins[] = {45, 43, 41, 39};
int columnPins[] = {37, 35, 33, 31};
//int rowPins[] = {49,47,45, 43};
//int columnPins[] = {41,39,37, 35};
char digitaMap[4][4] {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char secretDigits[4], testDigits[4];
enum state {SET, GUESS};
const int btnPin = 2;
int digitCount = 0;
int loseCount = 0;
int aRecord = 0, bRecord = 0; //recording right position and number
state gameState = SET;
void setup()
{
  Serial.begin(115200);
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("4 digits Game");
  for (int i = 0; i < 4; i++)
  {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], HIGH);
  }
  pinMode(btnPin, INPUT_PULLUP);
  delay(2000);
}

void loop()
{
  char c = getKey();
  switch (gameState) {
    case SET:
      lcd.setCursor(0, 0);
      lcd.print("Enter Secret:    ");
      lcd.setCursor(0, 1);
      loseCount = 0;

      if (digitCount == 0) {
        lcd.print("----              ");
      }
      if (c != 0) {

        secretDigits[digitCount] = c;
        lcd.setCursor(digitCount, 1);
        lcd.print(c);
        digitCount++;
        if (digitCount == 4) {
          if (checkRedundantNum(secretDigits)) {
            lcd.setCursor(0, 1);
            lcd.print("Redundant Numbers    ");
            delay(2000);
          }
          else {
            gameState = GUESS;

          }
          digitCount = 0;
        }
      }
      break;
    case GUESS:
      lcd.setCursor(0, 0);
      lcd.print("Enter Answer:    ");
      lcd.setCursor(0, 1);
      if (digitCount == 0) {
        lcd.print("----          ");
      }
      if (c != 0) {
        testDigits[digitCount] = c;
        lcd.setCursor(digitCount, 1);
        lcd.print(c);
        digitCount++;
        if (digitCount == 4) {
          gameState = GUESS;
          if (checkAnswer2()) {
            lcd.setCursor(0, 1);
            lcd.print("You Win!"        );
            delay(3000);
            gameState = SET;
          }
          else {
            loseCount++;
            lcd.setCursor(0, 1);
            lcd.print(aRecord);
            lcd.print('A');
            lcd.print(bRecord);
            lcd.print('B');
            delay(2000);
            lcd.setCursor(0, 1);
            int leftCount = 10 - loseCount;
            lcd.print(leftCount);
            lcd.print(" Times Left    ");
            delay(3000);

            if (loseCount == 10) {
              lcd.setCursor(0, 1);
              lcd.print("Game Over      ");
              delay(3000);
              gameState = SET;
            }
          }
          digitCount = 0;
          aRecord = bRecord = 0;
        }
      }
      break;
    default:
      Serial.print("No matching case.");
  }


}

int checkRedundantNum(char *ptr) {
  int redundantCount = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 1; j < 4 - i; j++) {
      if (*(ptr+i) == *(ptr+i+j)) {
        redundantCount++;
        Serial.println("i="+String(i));
        Serial.println("j="+String(j));
        Serial.println("testDigits[i]="+String(*(ptr+i)));
        Serial.println("testDigits[i+j]="+String(*(ptr+i+j)));
      }
    }

  }
//  lcd.setCursor(0, 1);
//  lcd.print("rCount:");
//  lcd.print(redundantCount);
//  delay(1000);
  return redundantCount;
}

bool checkAnswer() {
  for (int i = 0; i < 4; i++) {
    if (secretDigits[i] != testDigits[i]) {
      return 0;
    }
  }
  return 1;
}

bool checkAnswer2() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (testDigits[i] == secretDigits[j]) {
        if (i == j) {
          aRecord++;
        }
        else {
          bRecord++;
        }
      }
    }
  }
  if (aRecord == 4) {
    return 1;
  }
  else {
    return 0;
  }
}

char getKey() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(columnPins[i], LOW);
    for (int j = 0; j < 4; j++) {
      if (digitalRead(rowPins[j]) == LOW) {
        delay(20);
        while (digitalRead(rowPins[j]) == LOW);
        digitalWrite(columnPins[i], HIGH);
        return digitaMap[j][i];

      }
    }
    digitalWrite(columnPins[i], HIGH);
  }
  return 0;
}
