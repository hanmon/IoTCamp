
//透過IDE中Serial Monitor測試Echo
void setup() {
  //初始化序列埠:
  Serial.begin(115200);
  Serial.println("A test for Echo");
}
void loop() {
//  if(Serial.available()>0){
//    char c=Serial.read();
//    Serial.write(c);
//  }
}

void serialEvent()
{
    Serial.write(Serial.read());
}
