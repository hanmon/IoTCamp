//透過按壓pushbotton switch改變數位輸入腳的電壓準位，Pin11與Pin12皆為正向邏輯
const int poPin1 = 11, poPin2 = 12;
const int ledPin = 13;
boolean btnOneState = LOW, btnTwoState = LOW;
// the setup routine runs once when you press reset:
void setup() {
  //設定input pin與led pin的模式
  pinMode(poPin1, INPUT);
  pinMode(poPin2, INPUT);
  pinMode(ledPin, OUTPUT);
}
// the loop routine runs over and over again forever:
void loop() {
  //  讀取input pin電壓值，按下button時使led亮起
  btnOneState = digitalRead(poPin1);   // read the input pin1
  btnTwoState = digitalRead(poPin2);   // read the input pin2
  if (btnOneState == HIGH && btnTwoState == HIGH) {
    //keeping light on
    digitalWrite(ledPin, HIGH);
  }
  else if (btnOneState == HIGH && btnTwoState == LOW) {
    //blinking fast
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  else if (btnOneState == LOW && btnTwoState == HIGH) {
    //blinking slowly
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
