//每2秒在四位數七段顯示器顯示一個四位數隨機值
//Pin腳排列
//7段顯示器編號：  1 2 3 4 5  6  7   8  9  10  11  12
//代表：         E D d C G  D4  B  D3 D2  F   A   D1
//Arduino腳位：   2 3 4 5 6 7   8  9  10  11  12  13
//Author: Bruce Chiu
//Date:2019-07-21
int selectPins[] = {13, 10, 9, 7}; //D1,D2,D3,D4
//int selectPins[] = {11,10,9,8}; //D1,D2,D3,D4
int ledPins[] = {12, 8, 5, 3, 2, 11, 6, 4}; //ABCDEFGdp
byte digits[10] = {
  //ABCDEFGDp
  B11111100,//數字0
  B01100000,//數字1
  B11011010,//數字2
  B11110010,//數字3
  B01100110,//數字4
  B10110110,//數字5
  B00111110,//數字6
  B11100000,//數字7
  B11111110,//數字8
  B11100110,//數字9
};



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(selectPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(A0));
}

void loop() {
  static unsigned long lastTime = 0;
  static int randomValue=0;
  if(millis() - lastTime > 2000) {
    randomValue=random(0,10000);
    Serial.println(randomValue);
    lastTime=millis();
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
  delay(5);
  //Serial.print(unit);
  setDigit(tens, 2); //設定D3
  delay(5);
  //Serial.print(tens);
  setDigit(hundreds, 1); //設定D2
  delay(5);
  // Serial.print(hundreds);
  setDigit(thousands, 0); //設定D1
  delay(5);
  // Serial.println(thousands);
}

void setDigit(int digit, int position) {
  bool ledState;
  for (int i = 0; i < 4; i++) {
    if(i==position){
      digitalWrite(selectPins[position], LOW);
    }
    else{
      digitalWrite(selectPins[i], HIGH);
    }
    
  }
  for (int i = 0; i < 8; i++) {
    ledState = bitRead(digits[digit], i);
    digitalWrite(ledPins[7 - i], ledState);
  }
}
