const int ledPin=9;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  //快閃三次，週期1秒
  blinkLed(ledPin,500,3);
}

void loop() {
  // put your main code here, to run repeatedly:
  //慢閃，週期4秒
  blinkLed(ledPin,2000,1);
}

void blinkLed(int pin,int interval,int count){
  while(count>0){
    digitalWrite(pin,HIGH);
    delay(interval);
    digitalWrite(pin,LOW);
    delay(interval);
    count=count-1;
    //count--;
  }
}
