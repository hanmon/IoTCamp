void setup() {
  // put your setup code here, to run once:
  pinMode(7,INPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  (digitalRead(7))?digitalWrite(3,HIGH):digitalWrite(3,LOW);
}
