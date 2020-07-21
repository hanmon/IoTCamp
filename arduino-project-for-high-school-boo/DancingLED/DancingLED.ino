/*
 * Example of dancing LED
 * Components: 7 LEDs attached to D2~D8 of Arduino Uno/MEGA2560
 * Author:Bruce Chiu
 * Date:2019/07/28
 * Email:boo.chiu@gmail.com
 */
//定義用來控制LED的7個腳位
int ledPins[]={2,3,4,5,6,7,8};
//計算腳位數目
int numPins=sizeof(ledPins)/sizeof(int);
//設定每個LED點亮的時間長度
int wait=50;
void setup()
{ //設定各腳位為輸出
  for(int i=0;i<numPins;i++){
  	pinMode(ledPins[i], OUTPUT);
  }
}

void loop()
{ //從第1支腳依序掃描到最後1支，順序為第N支腳High->第N+1支腳High->第N支腳LOW
  for(int i=0;i<numPins-1;i++){
  	digitalWrite(ledPins[i],HIGH);
    delay(wait);
    digitalWrite(ledPins[i+1],HIGH);
    delay(wait);
    digitalWrite(ledPins[i],LOW);
    delay(wait);
  }
    //從最後1支腳依序掃描到到第一支，順序為第N支腳High->第N-1支腳High->第N支腳LOW
  for(int i=numPins-1;i>0;i--){
  	digitalWrite(ledPins[i],HIGH);
    delay(wait);
    digitalWrite(ledPins[i-1],HIGH);
    delay(wait);
    digitalWrite(ledPins[i],LOW);
    delay(wait);
  }
}
