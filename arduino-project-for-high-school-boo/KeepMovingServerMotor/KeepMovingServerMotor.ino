#include <Servo.h> //引用Servo函式庫
const int servoPin=12;
Servo myservo;//宣告Servo物件
// the setup routine runs once when you press reset:
void setup() {      
 //設定Servo Motor控制pin
 myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object
}
// the loop routine runs over and over again forever:
void loop() {
  for(int i=10;i<170;i++)
  {
    myservo.write(i);//設定ServoMotor轉動的位置
    delay(15);
  }
  for(int i=170;i>0;i--)
  {
    myservo.write(i);//設定ServoMotor轉動的位置
    delay(15);//等待Servo Motor轉動到定點
  }
}
