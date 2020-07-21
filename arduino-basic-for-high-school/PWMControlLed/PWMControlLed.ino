//以PWM腳位(3,5,6,9,10,11其中之一)控制LED亮度(適用Arduino板)
const int ledPin=12;
int brightness=0;
int increment=1;
int wait=20;
void setup() {      
 //由analogWrite驅動的腳位不需要設定模式 
}
// the loop routine runs over and over again forever:
void loop() {
//  led亮度由暗漸漸變亮，再由亮漸漸變暗，不斷循環
  if(brightness==255)
  {
    increment=-1;
  }
  else if(brightness==0)
  {
    increment=1;
  }
  brightness+=increment;
  analogWrite(ledPin,brightness);
  delay(wait);
}
