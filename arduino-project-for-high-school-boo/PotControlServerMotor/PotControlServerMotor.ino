#include <Servo.h> //引用Servo函式庫
const int servoPin = 12;
const int varPin = 0;
int val = 0;
Servo myservo;//宣告Servo物件
// the setup routine runs once when you press reset:
void setup() {
  //設定Servo Motor控制pin，由analogRead驅動的腳位不需要設定模式
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object
}
// the loop routine runs over and over again forever:
void loop() {
  //自varPin讀取類比電壓值（0~1023)
  val = analogRead(varPin); //讀取可變電阻輸出電壓
  val = map(val, 0, 1023, 10, 170); //調整數值到ServoMotor可接受的範圍
  myservo.write(val);//設定ServoMotor轉動的位置
  delay(15);//等待Servo Motor轉動到定點(15ms)
}
