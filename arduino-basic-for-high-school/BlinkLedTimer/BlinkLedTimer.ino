//測試millis()函式
unsigned long lastTime=0;
int interval=500;
const int ledPin=9;
bool ledState=LOW;
void setup(){
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);
}
void loop(){
  if(millis()-lastTime>interval){
    //ledState=!ledState;
    ledState^=1;
    digitalWrite(ledPin,ledState);
    lastTime=millis();
  }
}
