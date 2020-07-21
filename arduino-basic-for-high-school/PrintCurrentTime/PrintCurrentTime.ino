//測試millis()函式
unsigned long currentTime;

void setup(){
  Serial.begin(115200);
}
void loop(){
  //Serial.print("Time: ");
  currentTime = millis();
  //prints time since program started
  Serial.println(currentTime);
  // wait a second so as not to send massive amounts of data
  delay(1000);
}
