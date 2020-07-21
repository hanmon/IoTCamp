//在第二腳以正向邏輯接按鍵開關
//每三秒統計一次第二腳準位改變次數
const int extIntPin = 2; //for interrupt0
volatile int count = 0;
void setup() {
  Serial.begin(115200);
  pinMode(extIntPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(extIntPin), analyze, FALLING);

}
void loop() {
  delay(3000);
  Serial.print("Count of level change in 3 seconds:");
  Serial.println(count);
  count = 0;
}

void analyze() {
  count++;
}
