const int ledPin=13;

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // read from Serial2, send to Serial0:
  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
    if(inByte=='H'){
      digitalWrite(ledPin,HIGH);
    }
    else if(inByte=='L'){
      digitalWrite(ledPin,LOW);
    }
  }

  // read from Serial0, send to Serial2:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial2.write(inByte);
  }
}
