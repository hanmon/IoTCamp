int poLedPin = 8,neLedPin=9;  // LED 連接在D9
int poBtnPin = 2,neBtnPin=3;    // 按鈕連接在D2，使用下拉電阻實作正向邏輯
bool neBtnState = LOW,poBtnState=LOW;      // 存放讀取值的bool變數

void setup() {
  pinMode(neLedPin, OUTPUT);  // 設定D9為輸出
  pinMode(poLedPin, OUTPUT);  // 設定D8為輸出
  pinMode(poBtnPin, INPUT);    // 設定D2為輸入，正向邏輯
  pinMode(neBtnPin,   ); //設定D3為輸入，內部上拉，負向邏輯
}

void loop() {
  neBtnState = digitalRead(neBtnPin);   // 讀取輸入腳位
  poBtnState = digitalRead(poBtnPin);   // 讀取輸入腳位
  digitalWrite(neLedPin, !neBtnState);  // 依據輸入腳位的狀態設定LED狀態
  digitalWrite(poLedPin, poBtnState);  // 依據輸入腳位的狀態設定LED狀態
}
