//Arduino版"Hello,world!"
const int ledPin=9;
void setup() {
  pinMode(ledPin, OUTPUT);    // 設定ledPin腳位為輸出
}

void loop() {
  digitalWrite(ledPin, HIGH); // 設定ledPin輸出HIGH
  delay(1000);            // 等一秒
  digitalWrite(ledPin, LOW);  //設定ledPin輸出LOW
  delay(1000);            // 等一秒
}
