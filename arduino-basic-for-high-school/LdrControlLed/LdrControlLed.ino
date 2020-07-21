//透過10K電阻與LDR間的分壓，在A0腳位感知亮度的變化
//定義led與ldr pin腳位
const int ledPin=13;
const int ldrAOPin=1;
const int ldrDOPin=3;
int val=0;
// the setup routine runs once when you press reset:
void setup() {      
 //led pin為3，啟用Serial port以觀察類比輸入值，而由analogRead驅動的腳位不需要設定模式
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
  val=analogRead(ldrAOPin);//自ldr pin讀取類比電壓值（0~1023)
  delay(1000);
  Serial.println(val);//印出類比電壓數值
  //讀取D0的狀態
  digitalRead(ldrDOPin)?Serial.println("DO HIGH"):Serial.println("DO LOW");
  //亮度超過一半時熄滅LED，低於一半時點亮LED
  if(val>=256) 
        digitalWrite(ledPin,HIGH);
  else if(val<256)
        digitalWrite(ledPin,LOW);
}
