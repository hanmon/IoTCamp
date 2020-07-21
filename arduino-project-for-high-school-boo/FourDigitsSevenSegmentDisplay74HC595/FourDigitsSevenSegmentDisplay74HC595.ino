//每2秒在四位數七段顯示器顯示一個四位數隨機值
//Pin腳排列
//7段顯示器編號：  1 2 3 4 5  6  7   8  9  10  11  12
//代表：         E D d C G  D4  B  D3 D2  F   A   D1
//Arduino腳位：   2 3 4 5 6 7   8  9  10  11  12  13
//Author: Bruce Chiu
//Date:2019-07-21
//int selectPins[] = {13, 10, 9, 7}; //D1,D2,D3,D4
int selectPins[] = {11, 10, 9, 8}; //D1,D2,D3,D4
//int ledPins[] = {12, 8, 5, 3, 2, 11, 6, 4}; //ABCDEFGdp

// pin 4 of 74HC595 (SHCP/SRCLK)

const int bit_clock_pin = 4;

// pin 3 of 74HC595 (STCP/RCLK)

const int digit_clock_pin = 3;

// pin 2 of 74HC595 (DS/SER) 資料

const int data_pin = 2;

int wait=5;
const byte digit_pattern[16] =

{

  B00111111,  // 0

  B00000110,  // 1

  B01011011,  // 2

  B01001111,  // 3

  B01100110,  // 4

  B01101101,  // 5

  B01111101,  // 6

  B00000111,  // 7

  B01111111,  // 8

  B01101111,  // 9

  B01110111,  // A

  B01111100,  // b

  B00111001,  // C

  B01011110,  // d

  B01111001,  // E

  B01110001   // F

};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(selectPins[i], OUTPUT);
  }
//  for (int i = 0; i < 8; i++) {
//    pinMode(ledPins[i], OUTPUT);
//  }
  randomSeed(analogRead(A0));
  pinMode(data_pin, OUTPUT);

  pinMode(bit_clock_pin, OUTPUT);

  pinMode(digit_clock_pin, OUTPUT);
}

void loop() {
  static unsigned long lastTime = 0;
  static int randomValue = 0;
  if (millis() - lastTime > 2000) {
    randomValue = random(0, 10000);
    Serial.println(randomValue);
    lastTime = millis();
  }

  setNumber(randomValue);

}

void setNumber(int num) {
  //取個位數unit
  int unit = num % 10;
  //取10位數 tens
  int tens = num % 100 / 10;
  //取百位數 hundreds
  int hundreds = num % 1000 / 100;
  //取千位數 thousands
  int thousands = num / 1000;
  setDigit(unit, 3); //設定D4
  delay(wait);
  //Serial.print(unit);
  setDigit(tens, 2); //設定D3
 delay(wait);
  //Serial.print(tens);
  setDigit(hundreds, 1); //設定D2
  delay(wait);
  // Serial.print(hundreds);
  setDigit(thousands, 0); //設定D1
 delay(wait);
  // Serial.println(thousands);
}

void setDigit(int digit, int position) {
  bool ledState;
  for (int i = 0; i < 4; i++) {
    if (i == position) {
      digitalWrite(selectPins[position], LOW);
    }
    else {
      digitalWrite(selectPins[i], HIGH);
    }

  }
  //  for (int i = 0; i < 8; i++) {
  //    ledState = bitRead(digits[digit], i);
  //    digitalWrite(ledPins[7 - i], ledState);
  //  }
  update_one_digit(digit);
}

void update_one_digit(int data)
{

  int i;

  byte pattern;



  // get the digit pattern to be updated

  pattern = digit_pattern[data];



  // turn off the output of 74HC595

  digitalWrite(digit_clock_pin, LOW);



  // update data pattern to be outputed from 74HC595

  // because it's a common anode LED, the pattern needs to be inverted

  //shiftOut(data_pin, bit_clock_pin, LSBFIRST, ~pattern);
  shiftOut(data_pin, bit_clock_pin, MSBFIRST, pattern);



  // turn on the output of 74HC595

  digitalWrite(digit_clock_pin, HIGH);

}
