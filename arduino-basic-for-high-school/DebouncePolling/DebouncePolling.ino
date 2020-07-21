int btnPin = 2;
int ledPin = 9;
int debounceTime = 50;
boolean ledState = LOW;
boolean lastBtnState = LOW;
boolean btnState = LOW;
int stateChageCount = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Button pressed detection");
}

void loop() {
  debounce();
}

void debounce() {
  if (lastBtnState != digitalRead(btnPin)) {
    lastBtnState = digitalRead(btnPin);
    //start debouncing
    delay(debounceTime);

    if (lastBtnState == digitalRead(btnPin))
      stateChageCount++;
  }
  if (stateChageCount == 2) {
    toggleLED();
    Serial.println("Led Toggled");
    stateChageCount = 0;
  }
}

void toggleLED() {
  digitalWrite(ledPin, ledState ^= 1);
}
