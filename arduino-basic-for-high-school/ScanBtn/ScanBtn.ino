int btnPins[] = {4, 5, 6, 7, 8, 9, 10, 11};

int debounceTime = 20;

void setup() {
  for (int i = 0; i < sizeof(btnPins) / sizeof(int); i++) {
    pinMode(btnPins[i], INPUT_PULLUP);
  }
  Serial.begin(115200);
}

void loop() {
  int btnNum = getBtn();
  if (btnNum != 0) {
    Serial.print("Button ");
    Serial.print(btnNum);
    Serial.println(" has been pressed");
    btnNum = 0;
  }

}

int getBtn() {
  static bool lastBtnState[] = {1, 1, 1, 1, 1, 1, 1, 1};
  for (int i = 0; i < sizeof(btnPins) / sizeof(int); i++) {
    if (lastBtnState[i] != digitalRead(btnPins[i])) {
      lastBtnState[i] = digitalRead(btnPins[i]);
      //start debouncing
      for (int count = 0; count < 10; count++) {
        delay(1);
        if (lastBtnState[i] != digitalRead(btnPins[i])) {
          count = 0;
        }
      }
      if (lastBtnState[i] == HIGH) {
        return btnPins[i];
      }

    }
  }
  return 0;
}
