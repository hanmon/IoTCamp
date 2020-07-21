const int TrigPin = 11;
const int EchoPin = 12;
float cm;

void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop()
{
  delay(100);
  //發一個10ms的高脈衝去觸發TrigPin
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  cm = pulseIn(EchoPin, HIGH) / 58.0; //算成釐米
  cm = (int(cm * 100.0)) / 100.0; //保留兩位小數
  cm = cm - 0.62; // 　扣掉距離誤差值　
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}
