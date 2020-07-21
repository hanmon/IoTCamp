/*透過可變電阻中間腳讀取類比電壓，根據電壓值以PWM控制LED的亮度。
  pin3為Led pin，以A0 pin讀取類比電壓*/
//定義input pin腳位
const int ledPin = 12;
const int varPin = 0;
int brightness = 0; //存放亮度值

unsigned long lastCheckTime = 0;
// the setup routine runs once when you press reset:
void setup() {
  //設定串列埠以觀察類比電壓數值，led pin為3，由analogRead驅動的腳位不需要設定模式
  pinMode(ledPin,OUTPUT);
  Serial.begin(115200);
}
// the loop routine runs over and over again forever:
void loop() {
  //  自varPin讀取類比電壓值（0~1023)
  int value = analogRead(A1);
  //  將類比電壓值對應到0~255的值，作為led亮度參考值
  brightness = map(value, 0, 1023, 0, 255);
  analogWrite(ledPin, brightness);
  if (millis() - lastCheckTime > 1000) {
    Serial.println("brightness:" + String(brightness));
    lastCheckTime = millis();
  }

}
