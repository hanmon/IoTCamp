//本範例按鈕接法為負向邏輯
int btnPin = 2;
int ledPin = 8;
const int debounceTime = 20;
volatile unsigned long lastTriggeredTime = 0;
volatile bool lastBtnState = HIGH;

void setup() {
  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnPin), isr, CHANGE);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

}

//ISR for arduino
void isr() {
  if (millis() - lastTriggeredTime > debounceTime) {
    if (lastBtnState == LOW) {
      toggleLED();
    }
    lastBtnState ^= 1;
  }
  lastTriggeredTime = millis();
}

void toggleLED() {
  volatile static bool ledState = LOW;
  ledState ^= 1;
  digitalWrite(ledPin, ledState);
}
