const int led=13;
const int PIRout=24;
void setup() {  //定義針腳輸出入
  pinMode(led,OUTPUT); 
  pinMode(PIRout,INPUT);
  }
void loop() {
  int val=digitalRead(PIRout);  //讀取 PIR 輸出
  if (val==HIGH) {   //PIR 有偵測到時 : LED 閃一下
    digitalWrite(led,HIGH);
    delay(50);
    digitalWrite(led,LOW);
    delay(50);
    }
  else {  //PIR 沒有偵測到 : LED 暗
    digitalWrite(led,LOW);
    }
}
