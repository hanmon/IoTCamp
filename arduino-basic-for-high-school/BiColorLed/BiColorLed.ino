//驅動雙色LED，交替呈現綠、紅色
//定義led pin腳位
int gPin = 3;
int rPin = 4;
// the setup routine runs once when you press reset:
void setup() {                
  pinMode(gPin, OUTPUT); 
  pinMode(rPin, OUTPUT);   
}
// the loop routine runs over and over again forever:
void loop() {
  //交替顯示兩種顏色
      digitalWrite(gPin,HIGH); //綠色
      digitalWrite(rPin,LOW);
      delay(1000);
      digitalWrite(gPin,LOW);  
      digitalWrite(rPin,HIGH); //紅色
      delay(1000);
}